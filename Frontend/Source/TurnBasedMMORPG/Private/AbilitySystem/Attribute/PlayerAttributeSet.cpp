// 


#include "AbilitySystem/Attribute/PlayerAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UPlayerAttributeSet::OnRep_Exp(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Exp, Old);
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Exp, COND_None, REPNOTIFY_Always);
}
