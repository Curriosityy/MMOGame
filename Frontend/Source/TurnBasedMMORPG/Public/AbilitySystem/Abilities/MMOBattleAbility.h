#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MMOBaseGameplayAbility.h"
#include "Animation/AnimCurveTypes.h"
#include "MMOBattleAbility.generated.h"

UENUM(BlueprintType,
	meta = (Bitmask, BitmaskEnum="ECostFulfilled", Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECostFulfilled: uint8
{
	Fulfilled = 0,
	Mana = 1 << 0,
	Stamina = 1 << 1,
};

ENUM_CLASS_FLAGS(ECostFulfilled);
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOBattleAbility : public UMMOBaseGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText SkillName;
	UPROPERTY(EditDefaultsOnly)
	FText SkillDescription;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> SkillIcon;

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat APCurve;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> APCostEffectClass;

	UFUNCTION(BlueprintCallable)
	void CheckIfCostFulfilled(ECostFulfilled& Output) const;

	UFUNCTION(BlueprintCallable)
	int GetActionPointsRequired() const;

	UFUNCTION(BlueprintCallable)
	static bool CheckIfFlagHaveBit(const ECostFulfilled& First, const ECostFulfilled& Sec);

	FORCEINLINE TSoftObjectPtr<UTexture2D> GetIcon() const { return SkillIcon; }
};
