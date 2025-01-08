// 


#include "AbilitySystem/Abilities/MMOGameplayAbility_SendTransformToServer.h"

#include "Abilities/Tasks/AbilityTask_SpawnActor.h"


void UMMOGameplayAbility_SendTransformToServer::SendTransformToServer_Implementation(const FTransform& Transform,
	const FGameplayTag& Tag)
{
	ConsumedTransform = Transform;
	ConsumedTag = Tag;
	Server_Ability();
}

bool UMMOGameplayAbility_SendTransformToServer::SendTransformToServer_Validate(const FTransform& Transform,
                                                                               const FGameplayTag& Tag)
{
	return true;
}

UMMOGameplayAbility_SendTransformToServer::UMMOGameplayAbility_SendTransformToServer()
{
}
