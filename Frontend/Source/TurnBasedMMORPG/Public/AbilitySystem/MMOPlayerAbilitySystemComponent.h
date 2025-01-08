#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MMOAbilitySystemComponent.h"
#include "MMOPlayerAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBindTo, const FGameplayTag&, const UMMOBattleAbility*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityGranted, FGameplayAbilitySpec*);
class UMMOBattleAbility;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOPlayerAbilitySystemComponent : public UMMOAbilitySystemComponent
{
	GENERATED_BODY()

public:
	FOnBindTo OnAbilityBind;
	FOnAbilityGranted OnAbilityGranted;

	void BindBattleAbilityToShortcut(const TSubclassOf<UMMOBattleAbility>& AbilityToBind,
	                                 const FGameplayTag& TagToBindTo);

	void RemoveBattleBinding(const FGameplayTag& TagToBindTo);

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
};
