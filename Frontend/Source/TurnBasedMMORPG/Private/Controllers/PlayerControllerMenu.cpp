// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlayerControllerMenu.h"

#include "DebugHelper.h"
#include "MMOGameInstance.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"

void APlayerControllerMenu::OnServerInfoReceived(const FString& IpAndPort)
{
	MoveToServer(IpAndPort, PlayerName, GetGameInstance<UMMOGameInstance>()->GetUserSessionGUID());
}

void APlayerControllerMenu::OnCharacterSelected(const FCharacterFullInfoDTO& CharacterFullInfo)
{
	SetPlayerName(CharacterFullInfo.CharName);
}

void APlayerControllerMenu::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UNetAccountService>()->OnServerInfoReceived.AddDynamic(
		this, &ThisClass::OnServerInfoReceived);
	GetGameInstance()->GetSubsystem<UNetAccountService>()->OnCharacterSelected.AddDynamic(
		this, &ThisClass::OnCharacterSelected);
}
