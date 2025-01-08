// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PlayerControllerBase.h"
#include "Subsystems/NetAccountService.h"
#include "PlayerControllerMenu.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API APlayerControllerMenu : public APlayerControllerBase
{
	GENERATED_BODY()

	UFUNCTION()
	void OnServerInfoReceived(const FString& IpAndPort);

	UFUNCTION()
	void OnCharacterSelected(const FCharacterFullInfoDTO& CharacterFullInfo);

public:
	virtual void BeginPlay() override;
};
