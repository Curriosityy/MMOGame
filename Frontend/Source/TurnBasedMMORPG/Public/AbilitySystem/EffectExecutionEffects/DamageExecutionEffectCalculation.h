// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionEffectCalculation.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UDamageExecutionEffectCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	static int RandomWeaponDmg(const FGameplayEffectSpec& OwningSpec);
	float StatsValue(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                 const FGameplayEffectSpec& OwningSpec,
	                 const FAggregatorEvaluateParameters& EvaluateParams) const;
	static float CalculateEvasion(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                              const FAggregatorEvaluateParameters& EvaluateParams);
	static float CalculateAccuracy(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                               const FAggregatorEvaluateParameters& EvaluateParams);
	float GetArmorMitigation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                         const FAggregatorEvaluateParameters& EvaluateParams) const;

public:
	UDamageExecutionEffectCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
