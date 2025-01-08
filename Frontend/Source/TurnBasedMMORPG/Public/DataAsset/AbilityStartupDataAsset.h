// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityStartupDataAsset.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UMMOBaseGameplayAbility;
/**
 * 
 */
USTRUCT(Blueprintable)
struct FAbilityToAdd
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMMOBaseGameplayAbility> AbilityToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DynamicTagToAdd;
};

UCLASS()
class TURNBASEDMMORPG_API UAbilityStartupDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="StartupAbilities")
	TArray<TSubclassOf<UMMOBaseGameplayAbility>> StartupAbilities = {};

	UPROPERTY(EditDefaultsOnly, Category="StartupAbilities")
	TArray<FAbilityToAdd> StartupAbilitiesWithTags = {};

	UPROPERTY(EditDefaultsOnly, Category="StartupEffects")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects = {};


	virtual void GiveToASC(UAbilitySystemComponent* AbilitySystemComponent);
};
