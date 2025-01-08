#include "AbilitySystem/Abilities/TryAddAbilityToQueue.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "DTOs/TryAddAbilityDTO.h"


void UTryAddAbilityToQueue::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

UGameplayEffect* UTryAddAbilityToQueue::GetCostGameplayEffect() const
{
	return GetAbilityDTO() ? GetAbilityDTO()->GetAbility()->APCostEffectClass.GetDefaultObject() : nullptr;
}

const UTryAddAbilityDTO* UTryAddAbilityToQueue::GetAbilityDTO() const
{
	return Cast<UTryAddAbilityDTO>(CurrentEventData.OptionalObject);
}

bool UTryAddAbilityToQueue::CheckIsAPIsEnoughToQueue() const
{
	auto CurrentAP = Cast<UBaseAttributeSet>(
			GetAbilitySystemComponentFromActorInfo()->
			GetAttributeSet(UBaseAttributeSet::StaticClass()))->
		GetCurrentAbilityPoints();

	return (CurrentAP - GetAbilityDTO()->GetAbility()->GetActionPointsRequired()) >= 0;
}
