#include "AbilitySystem/MMOPlayerAbilitySystemComponent.h"

#include "DebugHelper.h"
#include "Messages.h"
#include "Tags.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "GameFramework/GameplayMessageSubsystem.h"

void UMMOPlayerAbilitySystemComponent::BindBattleAbilityToShortcut(const TSubclassOf<UMMOBattleAbility>& AbilityToBind,
                                                                   const FGameplayTag& TagToBindTo)
{
	check(TagToBindTo.IsValid())


	RemoveBattleBinding(TagToBindTo);
	FGameplayAbilitySpec* Spec = FindAbilitySpecFromClass(AbilityToBind);

	if (!Spec)
	{
		return;
	}

	Spec->DynamicAbilityTags.AddTag(TagToBindTo);
	MarkAbilitySpecDirty(*Spec);

	check(GetAbilitiesByDynamicTag(TagToBindTo))

	OnAbilityBind.Broadcast(TagToBindTo, Cast<UMMOBattleAbility>(Spec->Ability));
}

void UMMOPlayerAbilitySystemComponent::RemoveBattleBinding(const FGameplayTag& TagToBindTo)
{
	FGameplayAbilitySpec* Spec = GetAbilitiesByDynamicTag(TagToBindTo);

	if (!Spec)
	{
		return;
	}

	if (Spec->DynamicAbilityTags.HasTag(TagToBindTo))
	{
		Spec->DynamicAbilityTags.RemoveTag(TagToBindTo);
		MarkAbilitySpecDirty(*Spec);
	}

	OnAbilityBind.Broadcast(TagToBindTo, nullptr);
}

void UMMOPlayerAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	OnAbilityGranted.Broadcast(&AbilitySpec);
}
