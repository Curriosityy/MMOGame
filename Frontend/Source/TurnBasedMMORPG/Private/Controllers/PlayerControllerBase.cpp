// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlayerControllerBase.h"

#include "DebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/InputDataAsset.h"
#include "Engine/LocalPlayer.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Subsystems/EncryptionSubsystem.h"

APlayerControllerBase::APlayerControllerBase()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputData);
	check(InputData->DefaultMappingContext);

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputData->DefaultMappingContext, 0);
	}
}


void APlayerControllerBase::MoveToServer(const FString& IpAndPort, const FString& InPlayerName,
                                         const FString& InSessionGUID)
{
	check(!IpAndPort.IsEmpty());
	check(!InPlayerName.IsEmpty())
	check(!InSessionGUID.IsEmpty())

	const FString Key = IpAndPort + FString(TEXT("?ID=")) + GetGameInstance()->GetSubsystem<UEncryptionSubsystem>()->
	                                                                           EncryptNameAndSessionGUID(
		                                                                           PlayerName, InSessionGUID);
	Debug::Print(Key, this);
	ClientTravel(Key, TRAVEL_Absolute);
}


void APlayerControllerBase::SetPlayerName(const FString& InPlayerName)
{
	PlayerName = InPlayerName;
}

void APlayerControllerBase::SetSessionGUID(const FString& InPlayerSessionGUID)
{
	PlayerSessionGUID = InPlayerSessionGUID;
}

const FString& APlayerControllerBase::GetPlayerSessionGUID()
{
	return PlayerSessionGUID;
}

const FString& APlayerControllerBase::GetPlayerName()
{
	return PlayerName;
}
