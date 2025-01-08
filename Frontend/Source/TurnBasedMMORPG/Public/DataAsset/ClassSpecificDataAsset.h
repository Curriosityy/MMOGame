// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClassSpecificDataAsset.generated.h"

/**
 * 
 */

class UMMOBattleAbility;

UCLASS()
class TURNBASEDMMORPG_API UClassSpecificDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSoftClassPtr<UMMOBattleAbility>> Abilities;
};
