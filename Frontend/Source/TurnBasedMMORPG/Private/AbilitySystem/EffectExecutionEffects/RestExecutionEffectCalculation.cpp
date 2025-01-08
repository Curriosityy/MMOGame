#include "AbilitySystem/EffectExecutionEffects/RestExecutionEffectCalculation.h"

#include "Tags.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"

struct FRestCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Healing)

	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxStamina)
	DECLARE_ATTRIBUTE_CAPTUREDEF(StaminaRegen)

	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxMana)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ManaRegen)

	FRestCapture()
	{
		//DEFINE_ATTRIBUTE_CAPTUREDEF(Attribute set class, Property, Source/Targer,Snapshot (true/false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MaxHealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Healing, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MaxStamina, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, StaminaRegen, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MaxMana, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, ManaRegen, Source, false);
	}
};

static const FRestCapture& GetCapture()
{
	static FRestCapture Capture = {};
	return Capture;
}

float URestExecutionEffectCalculation::CalculateTickValue(const float MaxHealth, const float Period,
                                                          const int RegenTime)
{
	return (MaxHealth / RegenTime) * Period;
}

URestExecutionEffectCalculation::URestExecutionEffectCalculation()
{
	RelevantAttributesToCapture.Add(GetCapture().MaxHealthDef);
	RelevantAttributesToCapture.Add(GetCapture().HealingDef);

	RelevantAttributesToCapture.Add(GetCapture().MaxStaminaDef);
	RelevantAttributesToCapture.Add(GetCapture().StaminaRegenDef);

	RelevantAttributesToCapture.Add(GetCapture().ManaRegenDef);
	RelevantAttributesToCapture.Add(GetCapture().MaxManaDef);
}

void URestExecutionEffectCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();
	float Period = spec.GetPeriod();
	int RegenTime = BaseRegenTime;

	if (spec.CapturedSourceTags.GetActorTags().HasTag(MMOGameplayTags::Player_Status_Premium))
	{
		RegenTime = PremiumRegenTime;
	}

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = spec.CapturedTargetTags.GetAggregatedTags();
	float MaxHealth{};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetCapture().MaxHealthDef, EvaluateParams, MaxHealth);
	float MaxStamina{};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetCapture().MaxStaminaDef, EvaluateParams, MaxStamina);
	float MaxMana{};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetCapture().MaxManaDef, EvaluateParams, MaxMana);

	float TickValue = CalculateTickValue(MaxHealth, Period, RegenTime);

	OutExecutionOutput.AddOutputModifier({
		GetCapture().HealingProperty, EGameplayModOp::Additive,
		CalculateTickValue(MaxHealth, Period, RegenTime)
	});

	OutExecutionOutput.AddOutputModifier({
		GetCapture().StaminaRegenProperty, EGameplayModOp::Additive,
		CalculateTickValue(MaxStamina, Period, RegenTime)
	});

	OutExecutionOutput.AddOutputModifier({
		GetCapture().ManaRegenProperty, EGameplayModOp::Additive,
		CalculateTickValue(MaxMana, Period, RegenTime)
	});
}
