// 


#include "AbilitySystem/EffectExecutionEffects/EnemyChanceCalculate.h"


UEnemyChanceCalculate::UEnemyChanceCalculate()
{
}

void UEnemyChanceCalculate::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                   FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
}
