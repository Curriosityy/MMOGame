// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();

	//Attributes
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level = {1};
	ATTRIBUTE_ACCESSORS(ThisClass, Level);

	//Attributes
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength = {10};
	ATTRIBUTE_ACCESSORS(ThisClass, Strength);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Dexterity)
	FGameplayAttributeData Dexterity = {10};
	ATTRIBUTE_ACCESSORS(ThisClass, Dexterity);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence = {10};
	ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Wisdom)
	FGameplayAttributeData Wisdom = {10};
	ATTRIBUTE_ACCESSORS(ThisClass, Wisdom);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Faith)
	FGameplayAttributeData Faith = {10};
	ATTRIBUTE_ACCESSORS(ThisClass, Faith);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Charisma)
	FGameplayAttributeData Charisma = {10};
	ATTRIBUTE_ACCESSORS(ThisClass, Charisma);

	//Ability Points
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_MaxAbilityPoints)
	FGameplayAttributeData MaxAbilityPoints = {6};
	ATTRIBUTE_ACCESSORS(ThisClass, MaxAbilityPoints);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_CurrentAbilityPoints)
	FGameplayAttributeData CurrentAbilityPoints = {6};
	ATTRIBUTE_ACCESSORS(ThisClass, CurrentAbilityPoints);

	//Armor Stats
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Armour)
	FGameplayAttributeData Armour = {0};
	ATTRIBUTE_ACCESSORS(ThisClass, Armour);

	//Health
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_DamageTaken)
	FGameplayAttributeData DamageTaken = {0};
	ATTRIBUTE_ACCESSORS(ThisClass, DamageTaken);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health = {100};
	ATTRIBUTE_ACCESSORS(ThisClass, Health);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth = {100};
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Healing)
	FGameplayAttributeData Healing = {1};
	ATTRIBUTE_ACCESSORS(ThisClass, Healing);

	//Mana
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_ManaTaken)
	FGameplayAttributeData ManaTaken = {0};
	ATTRIBUTE_ACCESSORS(ThisClass, ManaTaken);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana = {100};
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana = {100};
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_ManaRegen)
	FGameplayAttributeData ManaRegen = {1};
	ATTRIBUTE_ACCESSORS(ThisClass, ManaRegen);

	//Stamina
	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_StaminaTaken)
	FGameplayAttributeData StaminaTaken = {0};
	ATTRIBUTE_ACCESSORS(ThisClass, StaminaTaken);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina = {100};
	ATTRIBUTE_ACCESSORS(ThisClass, Stamina);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina = {100};
	ATTRIBUTE_ACCESSORS(ThisClass, MaxStamina);

	UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_StaminaRegen)
	FGameplayAttributeData StaminaRegen = {1};
	ATTRIBUTE_ACCESSORS(ThisClass, StaminaRegen);

protected:
	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& Old);

	UFUNCTION()
	void OnRep_Armour(const FGameplayAttributeData& Old);

	//Stats
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Wisdom(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Faith(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Charisma(const FGameplayAttributeData& Old);
	//Heal
	UFUNCTION()
	void OnRep_DamageTaken(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& Old);

	//Mana
	UFUNCTION()
	void OnRep_ManaTaken(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& Old);

	//Stamina
	UFUNCTION()
	void OnRep_StaminaTaken(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_StaminaRegen(const FGameplayAttributeData& Old);

	//Ability points
	UFUNCTION()
	void OnRep_MaxAbilityPoints(const FGameplayAttributeData& Old);
	UFUNCTION()
	void OnRep_CurrentAbilityPoints(const FGameplayAttributeData& Old);

	void ZeroClamp(const FGameplayAttribute& Attribute, float& NewValue);
	void ClampMax(const FGameplayAttribute& Attribute, float& NewValue);

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
