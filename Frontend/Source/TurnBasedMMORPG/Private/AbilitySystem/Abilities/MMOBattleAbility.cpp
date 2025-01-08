#include "AbilitySystem/Abilities/MMOBattleAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"

void UMMOBattleAbility::CheckIfCostFulfilled(ECostFulfilled& Output) const
{
	const UBaseAttributeSet* as = Cast<UBaseAttributeSet>(GetAbilitySystemComponentFromActorInfo()->GetAttributeSet(
		UBaseAttributeSet::StaticClass()));


	FGameplayEffectSpec Spec(GetCostGameplayEffect(),
	                         MakeEffectContext(CurrentSpecHandle, CurrentActorInfo),
	                         GetAbilityLevel());

	Spec.CalculateModifierMagnitudes();
	const UBaseAttributeSet* Set = Cast<UBaseAttributeSet>(GetAbilitySystemComponentFromActorInfo()->GetAttributeSet(
		UBaseAttributeSet::StaticClass()));

	bool ManaCostFulfilled = true;
	bool StaminaCostFulfilled = true;

	for (int32 ModIdx = 0; ModIdx < Spec.Modifiers.Num(); ++ModIdx)
	{
		const FGameplayModifierInfo& ModDef = Spec.Def->Modifiers[ModIdx];
		const FModifierSpec& ModSpec = Spec.Modifiers[ModIdx];

		if (ModDef.Attribute == UBaseAttributeSet::GetManaTakenAttribute())
		{
			ManaCostFulfilled = Set->GetMana() - Set->GetManaTaken() - ModSpec.GetEvaluatedMagnitude() >= 0;
			continue;
		}

		StaminaCostFulfilled = Set->GetStamina() - Set->GetStaminaTaken() - ModSpec.GetEvaluatedMagnitude() >= 0;
	}


	Output |= !ManaCostFulfilled ? ECostFulfilled::Mana : ECostFulfilled::Fulfilled;
	Output |= !StaminaCostFulfilled ? ECostFulfilled::Stamina : ECostFulfilled::Fulfilled;
}

int UMMOBattleAbility::GetActionPointsRequired() const
{
	return APCurve.GetValueAtLevel(GetAbilityLevel());
}

bool UMMOBattleAbility::CheckIfFlagHaveBit(const ECostFulfilled& BitMask, const ECostFulfilled& BitValue)
{
	return (BitMask & BitValue) == BitValue;
}
