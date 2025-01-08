#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/HitResult.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MMOAbilityBlueprintLibrary.generated.h"

struct FGameplayEffectSpecHandle;
class UGameplayEffect;
class UMMOAbilitySystemComponent;
struct FGameplayEventData;

UENUM()
enum class EARPGSuccessType: uint8
{
	Successful,
	Unsuccessful
};

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOAbilityBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static void GenerateTryAddAbilityPayload(const FGameplayTag& InputTag, FGameplayEventData& OutEventData,
	                                         UMMOAbilitySystemComponent* Asc);
	static void GetHitUnderCursor(const UMMOAbilitySystemComponent* Asc, FHitResult& Hit);

	static void GenerateInteractionPayload(const FGameplayTag& InputTag, FGameplayEventData& OutEventData,
	                                       const UMMOAbilitySystemComponent* Asc);

	static void SetupSimpleEventData(FGameplayEventData& OutEventData, AActor* Instigator, AActor* Target);

public:
	UFUNCTION(BlueprintPure, meta = (Keywords = "MMOAbilities"))
	static void GenerateEventData(UMMOAbilitySystemComponent* ASC, const FGameplayTag& InputTag,
	                              FGameplayEventData& OutEventData);

	UFUNCTION(BlueprintPure, meta = (Keywords = "MMOAbilities"))
	static UMMOAbilitySystemComponent* GetMMOAbilityComponentSystem(APawn* Pawn);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "MMOAbilities"))
	static void MakeEffectSpecHandle(const UGameplayAbility* SourceAbility,
	                                 const UAbilitySystemComponent* SourceAsc,
	                                 const TSubclassOf<UGameplayEffect>& Effect,
	                                 const TMap<FGameplayTag, float>& EffectData,
	                                 FGameplayEffectSpecHandle& OutHandle);

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
	UFUNCTION(BlueprintCallable, meta = (Keywords = "MMOAbilities"))
	static void MakeDamageEffectMap(const TArray<float>& Values, TMap<FGameplayTag, float>& OutMap);

	static void Native_ApplyEffectSpecHandle(AActor* TargetActor,
	                                         UAbilitySystemComponent* InstigatorASC,
	                                         const FGameplayEffectSpecHandle& InSpecHandle,
	                                         FActiveGameplayEffectHandle& OutHandle);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability",
		meta = (DisplayName = "Apply Effect Spec Handle to target", ExpandEnumAsExecs="Success"))
	static void BP_ApplyEffectSpecHandle(AActor* TargetActor, UAbilitySystemComponent* InstigatorAsc,
	                                     const FGameplayEffectSpecHandle& InSpecHandle, EARPGSuccessType& Success,
	                                     FActiveGameplayEffectHandle& OutHandle);

	static void Native_AddLooseGameplayTagsToAll(UAbilitySystemComponent* Asc, const FGameplayTag& LooseGameplayTag);
};
