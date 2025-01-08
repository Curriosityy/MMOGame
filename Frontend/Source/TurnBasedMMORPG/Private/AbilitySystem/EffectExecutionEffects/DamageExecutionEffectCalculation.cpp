// 


#include "AbilitySystem/EffectExecutionEffects/DamageExecutionEffectCalculation.h"

#include "Tags.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

struct FSourceCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Charisma)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity)

	DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Faith)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Wisdom)


	FSourceCapture()
	{
		//DEFINE_ATTRIBUTE_CAPTUREDEF(Attribute set class, Property, Source/Targer,Snapshot (true/false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Dexterity, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Intelligence, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Wisdom, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Faith, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Charisma, Source, true);
	}
};

struct FTargetCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Wisdom)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Faith)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Charisma)

	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	DECLARE_ATTRIBUTE_CAPTUREDEF(Armour)

	FTargetCapture()
	{
		//DEFINE_ATTRIBUTE_CAPTUREDEF(Attribute set class, Property, Source/Targer,Snapshot (true/false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Strength, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Dexterity, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Intelligence, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Wisdom, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Faith, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Charisma, Target, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, DamageTaken, Target, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Armour, Target, true);
	}
};

static const FSourceCapture& GetSCapture()
{
	static FSourceCapture Capture = {};
	return Capture;
}

static const FTargetCapture& GetTCapture()
{
	static FTargetCapture Capture = {};
	return Capture;
}

UDamageExecutionEffectCalculation::UDamageExecutionEffectCalculation()
{
	RelevantAttributesToCapture.Add(GetSCapture().StrengthDef);
	RelevantAttributesToCapture.Add(GetSCapture().DexterityDef);
	RelevantAttributesToCapture.Add(GetSCapture().IntelligenceDef);
	RelevantAttributesToCapture.Add(GetSCapture().WisdomDef);
	RelevantAttributesToCapture.Add(GetSCapture().FaithDef);
	RelevantAttributesToCapture.Add(GetSCapture().CharismaDef);

	RelevantAttributesToCapture.Add(GetTCapture().StrengthDef);
	RelevantAttributesToCapture.Add(GetTCapture().DexterityDef);
	RelevantAttributesToCapture.Add(GetTCapture().IntelligenceDef);
	RelevantAttributesToCapture.Add(GetTCapture().WisdomDef);
	RelevantAttributesToCapture.Add(GetTCapture().FaithDef);
	RelevantAttributesToCapture.Add(GetTCapture().CharismaDef);
	RelevantAttributesToCapture.Add(GetTCapture().DamageTakenDef);
	RelevantAttributesToCapture.Add(GetTCapture().ArmourDef);
}

int UDamageExecutionEffectCalculation::RandomWeaponDmg(const FGameplayEffectSpec& OwningSpec)
{
	const float WeaponDamageLow = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Low);
	const float WeaponDamageMax = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Max);
	return UKismetMathLibrary::RandomInteger(WeaponDamageMax - WeaponDamageLow) + WeaponDamageLow;
}

float UDamageExecutionEffectCalculation::StatsValue(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                    const FGameplayEffectSpec& OwningSpec,
                                                    const FAggregatorEvaluateParameters& EvaluateParams) const
{
	const float StrMul = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Strength);
	const float DexMul = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Dexterity);
	const float IntMul = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Intelligence);
	const float WisMul = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Wisdom);
	const float FaiMul = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Faith);
	const float ChaMul = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Charisma);


	//Source values
	float SourceStrength = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().StrengthDef, EvaluateParams,
	                                                           SourceStrength);
	float SourceDexterity = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().DexterityDef, EvaluateParams,
	                                                           SourceDexterity);
	float SourceIntelligence = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().IntelligenceDef, EvaluateParams,
	                                                           SourceIntelligence);
	float SourceWisdom = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().WisdomDef, EvaluateParams, SourceWisdom);
	float SourceFaith = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().FaithDef, EvaluateParams, SourceFaith);
	float SourceCharisma = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().CharismaDef, EvaluateParams,
	                                                           SourceCharisma);

	return StrMul * SourceStrength + DexMul * SourceDexterity + IntMul * SourceIntelligence + SourceWisdom *
		WisMul + SourceFaith * FaiMul + SourceCharisma * ChaMul;
}

float UDamageExecutionEffectCalculation::CalculateEvasion(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParams)
{
	float TargetDexterity = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetTCapture().DexterityDef, EvaluateParams,
	                                                           TargetDexterity);
	float TargetWisdom = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetTCapture().WisdomDef, EvaluateParams, TargetWisdom);

	float sum = TargetDexterity + TargetWisdom;

	//TODO: RECALCULATE VALUES
	return (UKismetMathLibrary::Min(100, sum) * 0.25 + //25 chance
			UKismetMathLibrary::Max(UKismetMathLibrary::Min(200, sum - 100), 0) * 0.15 + //24
			UKismetMathLibrary::Max(UKismetMathLibrary::Min(300, sum - 300), 0) * 0.05 + //15
			UKismetMathLibrary::Max(UKismetMathLibrary::Min(600, sum - 600), 0) * 0.03) //18
		/ 100;
}

float UDamageExecutionEffectCalculation::CalculateAccuracy(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParams)
{
	float TargetDexterity = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().DexterityDef, EvaluateParams,
	                                                           TargetDexterity);
	float TargetWisdom = {};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSCapture().WisdomDef, EvaluateParams, TargetWisdom);

	float sum = TargetDexterity + TargetWisdom;

	//TODO: RECALCULATE VALUES
	return (UKismetMathLibrary::Min(100, sum) * 0.25 + //25 chance
			UKismetMathLibrary::Max(UKismetMathLibrary::Min(200, sum - 100), 0) * 0.15 + //24
			UKismetMathLibrary::Max(UKismetMathLibrary::Min(300, sum - 300), 0) * 0.05 + //15
			UKismetMathLibrary::Max(UKismetMathLibrary::Min(600, sum - 600), 0) * 0.03) //18
		/ 100;
}

float UDamageExecutionEffectCalculation::GetArmorMitigation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParams) const
{
	float TargetArmor{};
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetTCapture().ArmourDef, EvaluateParams,
	                                                           TargetArmor);

	//TODO: RECALCULATE VALUES
	float mitigation = UKismetMathLibrary::Max(30, TargetArmor * 0.2)
		+ UKismetMathLibrary::Max(30, TargetArmor * 0.1) +
		UKismetMathLibrary::Max(30, TargetArmor * 0.05);
	return UKismetMathLibrary::Min(mitigation / 100, .85);
}

void UDamageExecutionEffectCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& OwningSpec = ExecutionParams.GetOwningSpec();
	const FGameplayEffectContextHandle& Handle = OwningSpec.GetContext();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = OwningSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = OwningSpec.CapturedTargetTags.GetAggregatedTags();

	const float BaseHitChance = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_HitChance_Base);
	const float WeaponHitChance = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_HitChance_Weapon);

	const float AttackerAccuracy = CalculateAccuracy(ExecutionParams, EvaluateParams);
	const float DefenderEvasion = CalculateEvasion(ExecutionParams, EvaluateParams);

	const float HitChance = BaseHitChance * WeaponHitChance + AttackerAccuracy - DefenderEvasion;

	//TODO: Send hit chance to screen
	if (UKismetMathLibrary::RandomFloat() > HitChance)
	{
		UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(ExecutionParams.GetTargetAbilitySystemComponent(),
		                                                              MMOGameplayTags::Shared_Status_Dodged);

		return;
	}

	const float SkillDamage = OwningSpec.GetSetByCallerMagnitude(MMOGameplayTags::Shared_SetByCaller_SkillDamage);
	const float SkillMultiplier = OwningSpec.GetSetByCallerMagnitude(
		MMOGameplayTags::Shared_SetByCaller_SkillMultiplier);
	const int WeaponDmg = RandomWeaponDmg(OwningSpec);
	const float StatValue = StatsValue(ExecutionParams, OwningSpec, EvaluateParams);


	const int BaseDmg = (SkillDamage + WeaponDmg + StatValue) * (1 + SkillMultiplier);
	float FinalDamage = FMath::Floor(BaseDmg * (1 - GetArmorMitigation(ExecutionParams, EvaluateParams)));
	OutExecutionOutput.AddOutputModifier(
		{GetTCapture().DamageTakenProperty, EGameplayModOp::Additive, FinalDamage});
}
