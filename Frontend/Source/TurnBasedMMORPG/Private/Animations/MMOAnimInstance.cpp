// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MMOAnimInstance.h"

#include "Character/MMORPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMMOAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AMMORPGCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		MovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UMMOAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !MovementComponent)
	{
		return;
	}

	Velocity = OwningCharacter->GetVelocity();
	GroundSpeed = Velocity.Size2D();

	bHasAcceleration = MovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
