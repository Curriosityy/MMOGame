// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "EnemyInfoTableRow.generated.h"

/**
 * 
 */

class USkeletalMesh;
class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAbilityDataInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UGameplayAbility> Ability;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AbilityLevel{1};
};

USTRUCT(BlueprintType)
struct TURNBASEDMMORPG_API FEnemyInfoTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName MonsterName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Level{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Strength{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Dexterity{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Intelligence{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Wisdom{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Faith{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Charisma{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxAbilityPoints{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Armour{0};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxHealth{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxMana{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxStamina{1};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAbilityDataInfoRow> Abilities;
};
