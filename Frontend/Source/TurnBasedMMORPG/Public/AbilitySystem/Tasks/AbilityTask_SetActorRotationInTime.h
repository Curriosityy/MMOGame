// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SetActorRotationInTime.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);

UCLASS()
class TURNBASEDMMORPG_API UAbilityTask_SetActorRotationInTime : public UAbilityTask
{
	GENERATED_BODY()

	UAbilityTask_SetActorRotationInTime(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable,
		meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"),
		Category="Ability|Tasks")
	static UAbilityTask_SetActorRotationInTime* SetActorRotationInTime(UGameplayAbility* OwningAbility,
	                                                                   AActor* InActorToRotate, FRotator InRotation,
	                                                                   float InTime);
	UPROPERTY(Replicated)
	AActor* ActorToRotate;
	UPROPERTY(Replicated)
	FRotator Rotation;
	UPROPERTY(Replicated)
	float Time;
	UPROPERTY(Replicated)
	FRotator StartRotation;

	float StepTime{0};

public:
	UPROPERTY(BlueprintAssignable)
	FOnComplete OnComplete;

	virtual void TickTask(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
