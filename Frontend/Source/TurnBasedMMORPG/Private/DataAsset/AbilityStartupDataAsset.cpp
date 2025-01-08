// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/AbilityStartupDataAsset.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/MMOBaseGameplayAbility.h"

void UAbilityStartupDataAsset::GiveToASC(UAbilitySystemComponent* AbilitySystemComponent)
{
	for (const TSubclassOf<UMMOBaseGameplayAbility>& StartupAbility : StartupAbilities)
	{
		FGameplayAbilitySpec Spec{StartupAbility};
		Spec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		Spec.Level = 1;
		AbilitySystemComponent->GiveAbility(Spec);
	}

	for (const FAbilityToAdd& StartupAbility : StartupAbilitiesWithTags)
	{
		FGameplayAbilitySpec Spec{StartupAbility.AbilityToAdd};
		Spec.DynamicAbilityTags.AddTag(StartupAbility.DynamicTagToAdd);
		Spec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		Spec.Level = 1;
		AbilitySystemComponent->GiveAbility(Spec);
	}

	for (const TSubclassOf<UGameplayEffect>& StartupGameplayEffect : StartupGameplayEffects)
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(StartupGameplayEffect->GetDefaultObject<UGameplayEffect>(),
		                                                  1,
		                                                  AbilitySystemComponent->MakeEffectContext());
	}
}
