// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Navigation/PathFollowingComponent.h"
#include "AbilityTask_GoToPathfind.generated.h"

struct FPathFollowingResult;

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPathfindingCanceled);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPathfindingReached);

UCLASS()
class TURNBASEDMMORPG_API UAbilityTask_GoToPathfind : public UAbilityTask
{
	GENERATED_BODY()

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	TWeakObjectPtr<AController> MoverController;
	UPROPERTY()
	TWeakObjectPtr<UPathFollowingComponent> PFollowComp;

	static UPathFollowingComponent* InitNavigationControl(AController* Controller);

	void OnMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);

public:
	UPROPERTY(BlueprintAssignable)
	FOnPathfindingCanceled OnPathfindingCanceled;
	UPROPERTY(BlueprintAssignable)
	FOnPathfindingReached OnPathfindingReached;

	UFUNCTION(BlueprintCallable,
		meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"),
		Category="Ability|Tasks")
	static UAbilityTask_GoToPathfind* GoToPathfind(UGameplayAbility* OwningAbility,
	                                               AController* Controller,
	                                               const FVector& Location);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;
};
