// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MMOAbilitySystemComponent.generated.h"

class UMMOBattleAbility;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	FGameplayAbilitySpec* GetAbilitiesByDynamicTag(const FGameplayTag& DynamicTag);

	void OnAbilityInputPressed(const FGameplayTag& Tag);
	void OnAbilityInputReleased(const FGameplayTag& Tag);

	int GetActivatableAbilityIndexBasedOnDynamicTag(const FGameplayTag& DynamicTag) const;
	int GetActivatableAbilityIndexBasedOnClass(TSubclassOf<UGameplayAbility> Class) const;
};
