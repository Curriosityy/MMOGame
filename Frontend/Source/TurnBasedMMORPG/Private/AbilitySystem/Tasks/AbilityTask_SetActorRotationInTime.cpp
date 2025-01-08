// 


#include "AbilitySystem/Tasks/AbilityTask_SetActorRotationInTime.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

UAbilityTask_SetActorRotationInTime::UAbilityTask_SetActorRotationInTime(
	const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	bTickingTask = true;
}

UAbilityTask_SetActorRotationInTime* UAbilityTask_SetActorRotationInTime::SetActorRotationInTime(
	UGameplayAbility* OwningAbility, AActor* InActorToRotate, FRotator InRotation, float InTime)
{
	UAbilityTask_SetActorRotationInTime* MyObj = NewAbilityTask<UAbilityTask_SetActorRotationInTime>(OwningAbility);

	MyObj->ActorToRotate = InActorToRotate;
	MyObj->Rotation = InRotation;

	MyObj->Time = FMath::Max(InTime, 0.001f);
	MyObj->StartRotation = InActorToRotate->GetActorRotation();


	return MyObj;
}

void UAbilityTask_SetActorRotationInTime::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	StepTime += DeltaTime;

	const float Alpha = FMath::Min(StepTime / Time, 1);
	ActorToRotate->SetActorRotation(
		UKismetMathLibrary::RLerp(StartRotation, Rotation, Alpha, false));

	if (Alpha >= 1)
	{
		OnComplete.Broadcast();
		EndTask();
	}
}

void UAbilityTask_SetActorRotationInTime::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, ActorToRotate)
	DOREPLIFETIME(ThisClass, Rotation)
	DOREPLIFETIME(ThisClass, Time)
	DOREPLIFETIME(ThisClass, StartRotation)
}
