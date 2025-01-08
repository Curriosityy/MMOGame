// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ActivateAbilityAndWait.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnd);

UCLASS()
class TURNBASEDMMORPG_API UAbilityTask_ActivateAbilityAndWait : public UAbilityTask
{
	GENERATED_BODY()

	UFUNCTION()
	void OnEnd(const FAbilityEndedData& AbilityEndedData);

public:
	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnd OnAbilityEnd;

	UPROPERTY()
	TSubclassOf<UGameplayAbility> AbilityToActivate;

	UFUNCTION(BlueprintCallable,
		meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"),
		Category="Ability|Tasks")
	static UAbilityTask_ActivateAbilityAndWait* ActivateAbilityAndWait(UGameplayAbility* OwningAbility,
	                                                                   TSubclassOf<UGameplayAbility>
	                                                                   InAbilityToActivate);


	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;
};
