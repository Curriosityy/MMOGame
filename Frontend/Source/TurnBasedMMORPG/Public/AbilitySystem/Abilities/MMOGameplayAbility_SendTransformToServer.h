// 

#pragma once

#include "CoreMinimal.h"
#include "MMOBaseGameplayAbility.h"
#include "MMOGameplayAbility_SendTransformToServer.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOGameplayAbility_SendTransformToServer : public UMMOBaseGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	FTransform ConsumedTransform;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	FGameplayTag ConsumedTag;

public:
	UMMOGameplayAbility_SendTransformToServer();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void SendTransformToServer(const FTransform& Transform, const FGameplayTag& Tag);

	UFUNCTION(BlueprintImplementableEvent)
	void Server_Ability();
};
