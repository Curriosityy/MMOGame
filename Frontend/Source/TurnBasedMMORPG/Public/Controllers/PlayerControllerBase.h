// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class UInputDataAsset;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputDataAsset> InputData{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> RaycastingTypes{};

	//Sync over net?
	FString PlayerName;
	FString PlayerSessionGUID;

public:
	APlayerControllerBase();
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void MoveToServer(const FString& IpAndPort, const FString& InPlayerName, const FString& InSessionGUID);

	void SetPlayerName(const FString& InPlayerName);
	void SetSessionGUID(const FString& InPlayerSessionGUID);
	const FString& GetPlayerSessionGUID();
	const FString& GetPlayerName();
};
