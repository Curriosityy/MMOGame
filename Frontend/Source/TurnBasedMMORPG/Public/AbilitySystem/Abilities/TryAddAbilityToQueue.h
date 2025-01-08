#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MMOBaseGameplayAbility.h"
#include "TryAddAbilityToQueue.generated.h"

class UTryAddAbilityDTO;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UTryAddAbilityToQueue : public UMMOBaseGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	virtual UGameplayEffect* GetCostGameplayEffect() const override;
	UFUNCTION(BlueprintCallable)
	const UTryAddAbilityDTO* GetAbilityDTO() const;

	UFUNCTION(BlueprintCallable)
	bool CheckIsAPIsEnoughToQueue() const;
};
