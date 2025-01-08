// 


#include "BattleSystem/DamageSpecBuilder.h"

#include "AbilitySystemComponent.h"
#include "Tags.h"
#include "AbilitySystem/EffectExecutionEffects/DamageExecutionEffectCalculation.h"
#include "Engine/World.h"

struct FGameplayTag;

UDamageSpecBuilder* UDamageSpecBuilder::AddGameplayEffect(UGameplayEffect* GameplayEffect)
{
	Gameplay_Effect = GameplayEffect;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddStrMul(float StrMul)
{
	Str_Mul = StrMul;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddDexMul(float DexMul)
{
	Dex_Mul = DexMul;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddIntMul(float IntMul)
{
	Int_Mul = IntMul;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddWisMul(float WisMul)
{
	Wis_Mul = WisMul;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddFaiMul(float FaiMul)
{
	Fai_Mul = FaiMul;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddChaMul(float ChaMul)
{
	Cha_Mul = ChaMul;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddSkillHitChance(float SkillHitChance)
{
	SkillHit_Chance = SkillHitChance;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddWeaponHitChance(float WeaponHinChance)
{
	WeaponHit_Chance = WeaponHinChance;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddSkillDmg(float SkillDmg)
{
	Skill_Dmg = SkillDmg;
	return this;
}

UDamageSpecBuilder* UDamageSpecBuilder::AddSkillMul(float SkillMul)
{
	Skill_Mul = SkillMul;
	return this;
}


UDamageSpecBuilder* UDamageSpecBuilder::AddWeaponDmg(float LowDmg, float HighDamage)
{
	Weapon_Low_Dmg = LowDmg;
	Weapon_Hig_Dmg = HighDamage;
	return this;
}


FGameplayEffectSpec UDamageSpecBuilder::Build(UAbilitySystemComponent* Instigator)
{
	TMap<FGameplayTag, float> DamageCalculation;
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Strength, Str_Mul});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Dexterity, Dex_Mul});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Intelligence, Int_Mul});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Wisdom, Wis_Mul});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Faith, Fai_Mul});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Charisma, Cha_Mul});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_HitChance_Base, SkillHit_Chance});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_HitChance_Weapon, WeaponHit_Chance});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SkillDamage, Skill_Dmg});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Low, Weapon_Low_Dmg});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Max, Weapon_Hig_Dmg});
	DamageCalculation.Add({MMOGameplayTags::Shared_SetByCaller_SkillMultiplier, Skill_Mul});
	if (Gameplay_Effect == nullptr)
	{
		Gameplay_Effect = NewObject<UGameplayEffect>(Instigator->GetWorld());
		FGameplayEffectExecutionDefinition def;
		def.CalculationClass = UDamageExecutionEffectCalculation::StaticClass();
		Gameplay_Effect->Executions.Add(def);
	}

	FGameplayEffectContextHandle ContextHandle = Instigator->MakeEffectContext();
	ContextHandle.AddSourceObject(Instigator);
	ContextHandle.AddInstigator(Instigator->GetOwnerActor(), Instigator->GetAvatarActor());
	FGameplayEffectSpec OutEff = FGameplayEffectSpec(Gameplay_Effect, ContextHandle, 1);

	for (const TTuple<FGameplayTag, float>& Calculation : DamageCalculation)
	{
		OutEff.SetSetByCallerMagnitude(Calculation.Key, Calculation.Value);
	}

	return OutEff;
}
