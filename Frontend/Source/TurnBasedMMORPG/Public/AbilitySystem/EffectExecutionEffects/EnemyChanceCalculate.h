// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "EnemyChanceCalculate.generated.h"


/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UEnemyChanceCalculate : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UEnemyChanceCalculate();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
