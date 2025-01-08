// 

#pragma once

#include "CoreMinimal.h"
#include "MMOBaseGameplayAbility.h"
#include "Interfaces/Interactable.h"
#include "InteractAbilityBase.generated.h"

class IInteractable;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API UInteractAbilityBase : public UMMOBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool GetHitResult(FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	EInteractType GetInteractionType();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
};
