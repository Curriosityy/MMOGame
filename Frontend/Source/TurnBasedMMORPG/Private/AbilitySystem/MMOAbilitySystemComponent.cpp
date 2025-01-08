// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMOAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "Tags.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"


FGameplayAbilitySpec* UMMOAbilitySystemComponent::GetAbilitiesByDynamicTag(
	const FGameplayTag& DynamicTag)
{
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability == nullptr)
		{
			continue;
		}

		if (Spec.DynamicAbilityTags.HasTag(DynamicTag))
		{
			return const_cast<FGameplayAbilitySpec*>(&Spec);
		}
	}

	return {};
}

void UMMOAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& Tag)
{
	if (!Tag.IsValid())
	{
		return;
	}

	const int Idx = GetActivatableAbilityIndexBasedOnDynamicTag(Tag);

	if (-1 == Idx)
	{
		return;
	}

	const FGameplayAbilitySpec& AbilityToManage = GetActivatableAbilities()[Idx];


	if (Tag.MatchesTag(MMOGameplayTags::InputTag_Toggle) &&
		AbilityToManage.IsActive())
	{
		CancelAbilityHandle(AbilityToManage.Handle);

		return;
	}

	if (Tag.MatchesTag(MMOGameplayTags::InputTag_Event))
	{
		FGameplayEventData Data;
		UMMOAbilityBlueprintLibrary::GenerateEventData(this, Tag, Data);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), Data.EventTag, Data);
		return;
	}

	if (Tag.MatchesTag(MMOGameplayTags::InputTag_Interaction))
	{
		FGameplayEventData Data;
		UMMOAbilityBlueprintLibrary::GenerateEventData(this, Tag, Data);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), Data.EventTag, Data);
		return;
	}

	TryActivateAbility(AbilityToManage.Handle);
}

void UMMOAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& Tag)
{
	if (!Tag.IsValid() || !Tag.MatchesTag(MMOGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	const int Idx = GetActivatableAbilityIndexBasedOnDynamicTag(Tag);

	if (INDEX_NONE == Idx)
	{
		return;
	}

	if (GetActivatableAbilities()[Idx].IsActive())
	{
		CancelAbilityHandle(GetActivatableAbilities()[Idx].Handle);
	}
}

int UMMOAbilitySystemComponent::GetActivatableAbilityIndexBasedOnDynamicTag(const FGameplayTag& DynamicTag) const
{
	return ActivatableAbilities.Items.IndexOfByPredicate([DynamicTag](const FGameplayAbilitySpec& AbilitySpec)
	{
		return AbilitySpec.DynamicAbilityTags.HasTag(DynamicTag);
	});
}

int UMMOAbilitySystemComponent::GetActivatableAbilityIndexBasedOnClass(TSubclassOf<UGameplayAbility> Class) const
{
	return ActivatableAbilities.Items.IndexOfByPredicate([Class](const FGameplayAbilitySpec& AbilitySpec)
	{
		return AbilitySpec.Ability.GetClass() == Class;
	});
}
