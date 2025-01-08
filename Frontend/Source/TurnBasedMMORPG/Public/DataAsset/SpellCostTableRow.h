// 

#pragma once

#include "CoreMinimal.h"
#include "EnemyInfoTableRow.h"
#include "ScalableFloat.h"
#include "Animation/AnimCurveTypes.h"
#include "UObject/Object.h"
#include "SpellCostTableRow.generated.h"
/**
 * 
 */
USTRUCT()
struct TURNBASEDMMORPG_API FSpellCostTableRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FScalableFloat ManaCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FScalableFloat StaminaCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FScalableFloat AbilityPointCost;
};
