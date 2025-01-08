#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "Messages.generated.h"

class UMMOBattleAbility;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FBarUpdatedMessage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UMMOBattleAbility> Ability;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FQueueMessage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	TArray<UMMOBattleAbility*> Queue;
};


USTRUCT(BlueprintType)
struct FAbilityClickedMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;
};
