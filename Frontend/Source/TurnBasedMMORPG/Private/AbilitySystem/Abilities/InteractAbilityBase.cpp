// 


#include "AbilitySystem/Abilities/InteractAbilityBase.h"

bool UInteractAbilityBase::GetHitResult(FHitResult& HitResult)
{
	for (TSharedPtr<FGameplayAbilityTargetData>& GameplayAbilityTargetData : CurrentEventData.TargetData.Data)
	{
		if (FGameplayAbilityTargetData_SingleTargetHit* Hit = static_cast<FGameplayAbilityTargetData_SingleTargetHit*>(
			GameplayAbilityTargetData.Get()))
		{
			HitResult = Hit->HitResult;
			return true;
		}
	}

	return false;
}

EInteractType UInteractAbilityBase::GetInteractionType()
{
	EInteractType Type = EInteractType::None;
	FHitResult Result;

	if (!GetHitResult(Result))
	{
		return Type;
	}

	IInteractable* Interactable = Cast<IInteractable>(Result.GetActor());

	if (!Interactable)
	{
		return Type;
	}

	return Interactable->GetInteractionType();
}


void UInteractAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
