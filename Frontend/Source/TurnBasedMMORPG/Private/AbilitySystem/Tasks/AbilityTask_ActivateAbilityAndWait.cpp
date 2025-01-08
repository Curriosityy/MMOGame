// 


#include "AbilitySystem/Tasks/AbilityTask_ActivateAbilityAndWait.h"

#include "AbilitySystemComponent.h"
#include "DebugHelper.h"

UAbilityTask_ActivateAbilityAndWait* UAbilityTask_ActivateAbilityAndWait::ActivateAbilityAndWait(
	UGameplayAbility* OwningAbility, TSubclassOf<UGameplayAbility> InAbilityToActivate)
{
	UAbilityTask_ActivateAbilityAndWait* MyObj = NewAbilityTask<UAbilityTask_ActivateAbilityAndWait>(OwningAbility);

	check(InAbilityToActivate)

	MyObj->AbilityToActivate = InAbilityToActivate;

	return MyObj;
}

void UAbilityTask_ActivateAbilityAndWait::OnEnd(const FAbilityEndedData& AbilityEndedData)
{
	if (AbilityEndedData.AbilityThatEnded.GetClass() == AbilityToActivate)
	{
		OnAbilityEnd.Broadcast();
		EndTask();
	}
}

void UAbilityTask_ActivateAbilityAndWait::Activate()
{
	Super::Activate();
	//FGameplayAbilitySpec* specHandle = AbilitySystemComponent->FindAbilitySpecFromClass(AbilityToActivate);
	AbilitySystemComponent->OnAbilityEnded.AddUObject(this, &ThisClass::OnEnd);
	const ENetRole NetMode = GetAvatarActor()->GetLocalRole();
	Debug::Print(UEnum::GetValueAsString(NetMode), this);
	if (!AbilitySystemComponent->TryActivateAbilityByClass(AbilityToActivate))
	{
		OnAbilityEnd.Broadcast();
		EndTask();
	}
}

void UAbilityTask_ActivateAbilityAndWait::OnDestroy(bool bInOwnerFinished)
{
	AbilitySystemComponent->OnAbilityEnded.RemoveAll(this);
	Super::OnDestroy(bInOwnerFinished);
}
