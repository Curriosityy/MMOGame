// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameplayTagContainer.h"
#include "GameStructs.generated.h"

class UInputAction;
/**
 * 
 */
USTRUCT(BlueprintType)
struct TURNBASEDMMORPG_API FInputConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (Categories="InputTag"))
	FGameplayTag InputTag = {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = {};

	bool IsValid() const;
};
