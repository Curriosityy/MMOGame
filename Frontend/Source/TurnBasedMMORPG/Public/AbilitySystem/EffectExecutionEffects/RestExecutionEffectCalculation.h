#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "RestExecutionEffectCalculation.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API URestExecutionEffectCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int BaseRegenTime{45};
	UPROPERTY(EditDefaultsOnly)
	int PremiumRegenTime{25};

	static float CalculateTickValue(float MaxHealth, float Period, int RegenTime);

public:
	URestExecutionEffectCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
