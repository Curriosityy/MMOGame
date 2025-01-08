// Copyright 2023 Sabre Dart Studios


#include "GameModes/InGameGameMode.h"

#include "DebugHelper.h"
#include "Editor.h"
#include "MMOGameInstance.h"
#include "MMOPlayerState.h"
#include "ActorFactories/ActorFactoryPlayerStart.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "Character/MMORPGCharacter.h"
#include "Controllers/PlayerGameController.h"
#include "Engine/AssetManager.h"
#include "Engine/NavigationObjectBase.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameSession.h"
#include "GameState/InGameGameState.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "Subsystems/EncryptionSubsystem.h"
#include "Subsystems/NetAccountService.h"
#include "Subsystems/NetCharactersControllerService.h"
#include "Subsystems/NetServerInstanceService.h"

FString AInGameGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                       const FString& Options, const FString& Portal)
{
	FString error = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	checkf(GetWorld(), TEXT("AInGameGameMode::InitNewPlayer - No UWorld Found!"))
	Debug::Print(TEXT("InitNewPlayer Started"), this);
	UMMOGameInstance* GameInstance = Cast<UMMOGameInstance>(GetWorld()->GetGameInstance());
	checkf(GameInstance, TEXT("GameInstance need to inheriting from UMMOGameInstance!"))
	APlayerGameController* InGameController = Cast<APlayerGameController>(NewPlayerController);
	checkf(InGameController, TEXT("GameController need to inheriting from InGameController!"))
	FString EncryptedIDData = UGameplayStatics::ParseOption(Options, TEXT("ID"));

	if (!EncryptedIDData.IsEmpty())
	{
		FString PlayerName{}, SessionGUID{};
		GameInstance->GetSubsystem<UEncryptionSubsystem>()->DecryptNameAndSessionGUID(
			EncryptedIDData, PlayerName, SessionGUID);

		InGameController->SetPlayerName(PlayerName);
		InGameController->SetSessionGUID(SessionGUID);
		return error;
	}

#ifdef WITH_EDITOR

	if (GEditor)
	{
		const int ToUse = CharToUse++;
		InGameController->SetPlayerName(DefaultCharacters[ToUse].Name);
		InGameController->SetSessionGUID(DefaultCharacters[ToUse].GUID);
		InGameController->GetPlayerState<AMMOPlayerState>()->SetPlayerName(DefaultCharacters[ToUse].Name);
		//Editor mode
		return error;
	}

#endif


	error += "Unauthorized!";
	GameSession->KickPlayer(NewPlayerController, FText::FromString(error));
	return error;
}

void AInGameGameMode::ZoneInfoReceived(const FZoneInstanceFullInfoDTO& ZoneInstanceFullInfoDto)
{
	CurrentZoneInstanceInfo = ZoneInstanceFullInfoDto;
}

void AInGameGameMode::OnCharInfoReceived(const FFullCharInfo& FullCharInfo)
{
	Debug::Print(
		FString::Printf(TEXT("AInGameGameMode::OnCharInfoReceived %s"), *FullCharInfo.CharacterData.CharacterName),
		this);
	APlayerController* Player{};
	WaitingPlayers.RemoveAndCopyValue(FullCharInfo.UserSessionGUID, Player);

	if (Player)
	{
		APlayerGameController* pgc = Cast<APlayerGameController>(Player);
		pgc->SetupPositionData(FullCharInfo);
		SpawnSoftPawnAndPossess(
			{pgc->StartRotation, pgc->StartLocation}, pgc->GetDefaultPawnClass(), pgc);
	}
}

void AInGameGameMode::StartPlay()
{
	if (HasAuthority())
	{
		FString CommandLineZoneInstanceID;
		FParse::Value(FCommandLine::Get(), TEXT("zoneinstanceid="), CommandLineZoneInstanceID);
		ZoneInstanceID = FCString::Atoi(*CommandLineZoneInstanceID);

#ifdef WITH_EDITOR
		ZoneInstanceID = 999989;
#endif


		Debug::Print(FString::Printf(TEXT("OWSGameMode::StartPlay - ZoneInstanceID: %i"), ZoneInstanceID), this);
		UNetServerInstanceService* serv = GetGameInstance()->GetSubsystem<UNetServerInstanceService>();
		serv->OnZoneInstanceInfoReceived.AddDynamic(this, &ThisClass::ZoneInfoReceived);
		GetGameInstance()->GetSubsystem<UNetCharactersControllerService>()->OnCharacterReceived.AddDynamic(
			this, &ThisClass::OnCharInfoReceived);
		//Lookup which Zone this server is running for and get the ZoneName into IAmZoneName var
		serv->GetZoneInstanceFromZoneInstanceID(ZoneInstanceID);

		//Change Status of the Zone Instance to 2 (ready for players to connect)
		serv->UpdateNumberOfPlayers(ZoneInstanceID, 0);

		SetMatchState(MatchState::WaitingToStart);
	}
}

void AInGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Debug::Print(FString::Printf(TEXT("On AInGameGameMode::PostLogin %s"), *NewPlayer->GetName()), this);
	FString SessionGuid = Cast<APlayerGameController>(NewPlayer)->GetPlayerSessionGUID();
	Debug::Print(FString::Printf(TEXT("Send await on %s"), *SessionGuid), this);
	WaitingPlayers.Add(SessionGuid, NewPlayer);
	GetGameInstance()->GetSubsystem<UNetCharactersControllerService>()->GetCharacterByName(
		Cast<APlayerGameController>(NewPlayer)->GetPlayerName(), SessionGuid);

	Super::PostLogin(NewPlayer);
}

void AInGameGameMode::OnPostLogin(AController* NewPlayer)
{
	Debug::Print("AInGameGameMode::OnPostLogin", this);
	ConnectedPlayers.Add(Cast<APlayerGameController>(NewPlayer));
}

void AInGameGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
	ConnectedPlayers.Add(Cast<APlayerGameController>(NewPC));
}

void AInGameGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	ConnectedPlayers.Remove(Cast<APlayerGameController>(Exiting));
}


void AInGameGameMode::SpawnSoftPawnAndPossess(const FTransform& SpawnPosition,
                                              const TSoftClassPtr<APawn>& PawnToSpawn,
                                              AController* Controller) const
{
	UAssetManager::GetStreamableManager().
		RequestAsyncLoad(PawnToSpawn.ToSoftObjectPath(),
		                 [SpawnPosition,PawnToSpawn,Controller,this]()
		                 {
			                 if (!PawnToSpawn.Get())
			                 {
				                 return;
			                 }

			                 APawn* pawn = GetWorld()->SpawnActorDeferred<
				                 APawn>(PawnToSpawn.Get(), SpawnPosition, Controller);
			                 Controller->Possess(pawn);
			                 pawn->FinishSpawning(SpawnPosition);
		                 });
}
