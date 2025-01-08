// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attribute/MonsterAttributeSet.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestsFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UTestsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void Native_GetAttributeSet(UWorld* World, UPlayerAttributeSet*& AttributeSet);
	static void Native_GetAttributeSet(UWorld* World, UMonsterAttributeSet*& AttributeSet);
	static UGameplayEffect* Native_LoadGameplayEffect(const FString& Path);
	static UGameplayEffect* Native_GenerateSimpleAttriubuteGameplayEffect(
		UWorld* World, float Value, EGameplayModOp::Type ModOp,
		const FGameplayAttribute& Attribute);
	static UGameplayEffect* Native_GenerateDamageCalculationGameplayEffect(UWorld* World);
	static void Native_GenerateDamageSpec(UWorld* World, const UPlayerAttributeSet* PlayerAttributeSet,
	                                      FGameplayEffectSpec& NewSpec,
	                                      float Str_Mul = 0,
	                                      float Dex_Mul = 0,
	                                      float Int_Mul = 0,
	                                      float Wis_Mul = 0,
	                                      float Fai_Mul = 0,
	                                      float Cha_Mul = 0,
	                                      float SkillHit_Chance = 0,
	                                      float WeaponHit_Chance = 0,
	                                      float SkillDmg = 0,
	                                      float Weapon_Low_Dmg = 0,
	                                      float Weapon_Hig_Dmg = 0);
};
