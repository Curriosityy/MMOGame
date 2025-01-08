// 


#include "FunctionLibraries/TestsFunctionLibrary.h"
#include "Engine/Engine.h"
#include "GameplayEffect.h"
#include "MMOPlayerState.h"
#include "AbilitySystem/Attribute/MonsterAttributeSet.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "AbilitySystem/EffectExecutionEffects/DamageExecutionEffectCalculation.h"
#include "Character/MonsterCharacter.h"
#include "Character/PlayerCharacter.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"
#include "Tests/AutomationEditorCommon.h"
#include "UObject/ConstructorHelpers.h"

void UTestsFunctionLibrary::Native_GetAttributeSet(UWorld* World, UPlayerAttributeSet*& AttributeSet)
{
	AMMOPlayerState* ActorOwner = World->SpawnActor<AMMOPlayerState>();
	APlayerCharacter* PPawn = World->SpawnActor<APlayerCharacter>();
	ActorOwner->GetAbilitySystemComponent()->InitStats(UPlayerAttributeSet::StaticClass(), nullptr);
	TArray<UAttributeSet*> Spawned = ActorOwner->GetAbilitySystemComponent()->GetSpawnedAttributes();
	ActorOwner->GetAbilitySystemComponent()->InitAbilityActorInfo(ActorOwner, PPawn);
	AttributeSet = Cast<UPlayerAttributeSet>(Spawned[0]);
}

void UTestsFunctionLibrary::Native_GetAttributeSet(UWorld* World, UMonsterAttributeSet*& AttributeSet)
{
	AMonsterCharacter* ActorOwner = World->SpawnActor<AMonsterCharacter>();
	ActorOwner->GetAbilitySystemComponent()->InitStats(UMonsterAttributeSet::StaticClass(), nullptr);
	TArray<UAttributeSet*> Spawned = ActorOwner->GetAbilitySystemComponent()->GetSpawnedAttributes();
	ActorOwner->GetAbilitySystemComponent()->InitAbilityActorInfo(ActorOwner, ActorOwner);
	AttributeSet = Cast<UMonsterAttributeSet>(Spawned[0]);
}


UGameplayEffect* UTestsFunctionLibrary::Native_LoadGameplayEffect(const FString& Path)
{
	TSoftObjectPtr<UGameplayEffect> SoftPtr = TSoftObjectPtr<UGameplayEffect>(FSoftObjectPath(Path));
	return SoftPtr.LoadSynchronous();
}

UGameplayEffect* UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(UWorld* World,
	const float Value,
	const EGameplayModOp::Type ModOp,
	const FGameplayAttribute& Attribute)
{
	UGameplayEffect* ge = NewObject<UGameplayEffect>(World);
	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = Attribute;
	ModifierInfo.ModifierOp = ModOp;
	ModifierInfo.ModifierMagnitude = FScalableFloat(Value);
	ge->Modifiers.Add(ModifierInfo);
	return ge;
}

UGameplayEffect* UTestsFunctionLibrary::Native_GenerateDamageCalculationGameplayEffect(UWorld* World)
{
	UGameplayEffect* ge = NewObject<UGameplayEffect>(World);
	FGameplayEffectExecutionDefinition def;
	def.CalculationClass = UDamageExecutionEffectCalculation::StaticClass();
	ge->Executions.Add(def);
	return ge;
}

void UTestsFunctionLibrary::Native_GenerateDamageSpec(UWorld* World,
                                                      const UPlayerAttributeSet* PlayerAttributeSet,
                                                      FGameplayEffectSpec& OutEff,
                                                      float Str_Mul,
                                                      float Dex_Mul,
                                                      float Int_Mul,
                                                      float Wis_Mul,
                                                      float Fai_Mul,
                                                      float Cha_Mul,
                                                      float SkillHit_Chance,
                                                      float WeaponHit_Chance,
                                                      float SkillDmg,
                                                      float Weapon_Low_Dmg,
                                                      float Weapon_Hig_Dmg)
{
	/*
* Values.NUM() == 11
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Strength, Values[0]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Dexterity, Values[1]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Intelligence, Values[2]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Wisdom, Values[3]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Faith, Values[4]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Charisma, Values[5]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_HitChance_Base, Values[6]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_HitChance_Weapon, Values[7]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_SkillDamage, Values[8]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Low, Values[9]});
* MapToPopulate.Add({MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Max, Values[10]});
*/
	TMap<FGameplayTag, float> DamageCalculation;
	UMMOAbilityBlueprintLibrary::MakeDamageEffectMap({
		                                                 Str_Mul, Dex_Mul, Int_Mul, Wis_Mul, Fai_Mul, Cha_Mul,
		                                                 SkillHit_Chance, WeaponHit_Chance, SkillDmg, Weapon_Low_Dmg,
		                                                 Weapon_Hig_Dmg
	                                                 }, DamageCalculation);
	UGameplayEffect* DamageCalculationEffect =
		Native_GenerateDamageCalculationGameplayEffect(World);

	FGameplayEffectContextHandle ContextHandle = PlayerAttributeSet->GetOwningAbilitySystemComponent()->
	                                                                 MakeEffectContext();
	ContextHandle.AddSourceObject(PlayerAttributeSet);

	OutEff = FGameplayEffectSpec(DamageCalculationEffect, ContextHandle, 1);

	for (const TTuple<FGameplayTag, float>& Calculation : DamageCalculation)
	{
		OutEff.SetSetByCallerMagnitude(Calculation.Key, Calculation.Value);
	}
}
