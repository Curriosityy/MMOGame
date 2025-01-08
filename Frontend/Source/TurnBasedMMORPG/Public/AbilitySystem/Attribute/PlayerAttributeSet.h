// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UPlayerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Exp)
	FGameplayAttributeData Exp = {1};
	ATTRIBUTE_ACCESSORS(ThisClass, Exp);

	UFUNCTION()
	void OnRep_Exp(const FGameplayAttributeData& Old);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
