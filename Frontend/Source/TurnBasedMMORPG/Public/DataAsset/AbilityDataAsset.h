#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityDataAsset.generated.h"

struct FGameplayTag;
class UMMOBattleAbility;
class UMMOBaseGameplayAbility;
/**
 * 
 */
USTRUCT(Blueprintable)
struct FBindingStruct
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta=(AllowPrivateAccess))
	TSubclassOf<UMMOBattleAbility> Ability;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
		meta=(AllowPrivateAccess, Title="InputTag", Categories="InputTag"))
	FGameplayTag InputTag;
};

UCLASS()
class TURNBASEDMMORPG_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess))
	TArray<FBindingStruct> Bindings;
};
