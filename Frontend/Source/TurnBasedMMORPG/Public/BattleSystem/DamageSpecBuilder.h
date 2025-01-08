// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "UObject/Object.h"
#include "DamageSpecBuilder.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UDamageSpecBuilder : public UObject
{
	GENERATED_BODY()

	float Str_Mul{0};
	float Dex_Mul{0};
	float Int_Mul{0};
	float Wis_Mul{0};
	float Fai_Mul{0};
	float Cha_Mul{0};
	float SkillHit_Chance{0};
	float WeaponHit_Chance{0};
	float Skill_Dmg{0};
	float Weapon_Low_Dmg{0};
	float Weapon_Hig_Dmg{0};
	float Skill_Mul{0};

	UPROPERTY()
	UGameplayEffect* Gameplay_Effect{};

public:
	UDamageSpecBuilder* AddGameplayEffect(UGameplayEffect* GameplayEffect);
	UDamageSpecBuilder* AddStrMul(float StrMul);
	UDamageSpecBuilder* AddDexMul(float DexMul);
	UDamageSpecBuilder* AddIntMul(float IntMul);
	UDamageSpecBuilder* AddWisMul(float WisMul);
	UDamageSpecBuilder* AddFaiMul(float FaiMul);
	UDamageSpecBuilder* AddChaMul(float ChaMul);
	UDamageSpecBuilder* AddSkillHitChance(float SkillHitChance);
	UDamageSpecBuilder* AddWeaponHitChance(float WeaponHinChance);
	UDamageSpecBuilder* AddSkillDmg(float SkillDmg);
	UDamageSpecBuilder* AddSkillMul(float SkillMul);
	UDamageSpecBuilder* AddWeaponDmg(float LowDmg, float HighDamage);
	FGameplayEffectSpec Build(UAbilitySystemComponent* Instigator);
};
