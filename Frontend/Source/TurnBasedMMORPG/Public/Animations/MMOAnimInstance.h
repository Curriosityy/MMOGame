// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MMOAnimInstance.generated.h"

class UCharacterMovementComponent;
class AMMORPGCharacter;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TObjectPtr<AMMORPGCharacter> OwningCharacter = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TObjectPtr<UCharacterMovementComponent> MovementComponent = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData", meta=(AllowPrivateAccess))
	FVector Velocity = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData", meta=(AllowPrivateAccess))
	float GroundSpeed = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData", meta=(AllowPrivateAccess))
	bool bHasAcceleration = {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData", meta=(AllowPrivateAccess))
	float LocomotionDirection = {};

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
