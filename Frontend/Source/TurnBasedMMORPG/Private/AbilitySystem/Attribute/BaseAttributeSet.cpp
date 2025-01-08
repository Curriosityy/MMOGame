// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/BaseAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Tags.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::OnRep_Level(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Level, Old);
}

void UBaseAttributeSet::OnRep_Armour(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Armour, Old);
}

void UBaseAttributeSet::OnRep_Strength(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Strength, Old);
}


void UBaseAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Dexterity, Old);
}

void UBaseAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Intelligence, Old);
}

void UBaseAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Wisdom, Old);
}

void UBaseAttributeSet::OnRep_Faith(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Faith, Old);
}

void UBaseAttributeSet::OnRep_Charisma(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Charisma, Old);
}

void UBaseAttributeSet::OnRep_DamageTaken(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, DamageTaken, Old);
}

void UBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, Old);
}

void UBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, Old);
}

void UBaseAttributeSet::OnRep_Healing(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Healing, Old);
}

void UBaseAttributeSet::OnRep_ManaTaken(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ManaTaken, Old);
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, Old);
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, Old);
}

void UBaseAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ManaRegen, Old);
}

void UBaseAttributeSet::OnRep_StaminaTaken(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, StaminaTaken, Old);
}

void UBaseAttributeSet::OnRep_Stamina(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Stamina, Old);
}

void UBaseAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxStamina, Old);
}

void UBaseAttributeSet::OnRep_StaminaRegen(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, StaminaRegen, Old);
}

void UBaseAttributeSet::OnRep_MaxAbilityPoints(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxAbilityPoints, Old);
}

void UBaseAttributeSet::OnRep_CurrentAbilityPoints(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CurrentAbilityPoints, Old);
}


void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//UPROPERTY(BlueprintReadOnly, Category="Values", ReplicatedUsing = OnRep_Strength)

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Level, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Wisdom, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Faith, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Charisma, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Armour, COND_None, REPNOTIFY_Always);

	//HEALTH
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, DamageTaken, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Healing, COND_None, REPNOTIFY_Always);

	//Stamina
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StaminaTaken, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StaminaRegen, COND_None, REPNOTIFY_Always);

	//Mana
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ManaTaken, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ManaRegen, COND_None, REPNOTIFY_Always);

	//Ability Points
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxAbilityPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CurrentAbilityPoints, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::ZeroClamp(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		return;
	}
	if (Attribute == GetMaxHealthAttribute() || Attribute == GetMaxManaAttribute() || Attribute ==
		GetMaxStaminaAttribute() || Attribute == GetLevelAttribute())
	{
		NewValue = UKismetMathLibrary::Max(NewValue, 1);
		return;
	}

	NewValue = UKismetMathLibrary::Max(NewValue, 0);
}

void UBaseAttributeSet::ClampMax(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = UKismetMathLibrary::Min(NewValue, GetMaxHealth());
		return;
	}

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = UKismetMathLibrary::Min(NewValue, GetMaxStamina());
		return;
	}

	if (Attribute == GetCurrentAbilityPointsAttribute())
	{
		NewValue = UKismetMathLibrary::Min(NewValue, GetMaxAbilityPoints());
		return;
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = UKismetMathLibrary::Min(NewValue, GetMaxMana());
		return;
	}

	if (Attribute == GetMaxHealthAttribute() && NewValue < GetHealth())
	{
		SetHealth(NewValue);
		return;
	}

	if (Attribute == GetMaxStaminaAttribute() && NewValue < GetStamina())
	{
		SetStamina(NewValue);
		return;
	}

	if (Attribute == GetMaxManaAttribute() && NewValue < GetMana())
	{
		SetMana(NewValue);
	}

	if (Attribute == GetMaxAbilityPointsAttribute() && NewValue < GetCurrentAbilityPoints())
	{
		SetCurrentAbilityPoints(NewValue);
	}
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Death))
	{
		//Death attribute

		NewValue = Attribute.GetNumericValue(this);
		return;
	}

	ZeroClamp(Attribute, NewValue);

	ClampMax(Attribute, NewValue);

	if (Attribute == GetHealthAttribute() && NewValue <= 0)
	{
		UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(GetOwningAbilitySystemComponent(),
		                                                              MMOGameplayTags::Shared_Status_Death);
	}
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//TODO:Refactor
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const int Damage = GetDamageTaken();
		SetDamageTaken(0);
		const int CurrentHealth = GetHealth();
		SetHealth(CurrentHealth - Damage);
		return;
	}

	if (Data.EvaluatedData.Attribute == GetManaTakenAttribute())
	{
		const int Damage = GetManaTaken();
		SetManaTaken(0);
		const int CurrentValue = GetMana();
		SetMana(CurrentValue - Damage);
		return;
	}

	if (Data.EvaluatedData.Attribute == GetStaminaTakenAttribute())
	{
		const int Damage = GetStaminaTaken();
		SetStaminaTaken(0);
		const int CurrentValue = GetStamina();
		SetStamina(CurrentValue - Damage);
		return;
	}

	if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		const int Regen = GetHealing();
		SetHealing(0);
		const int CurrentHealth = GetHealth();
		SetHealth(CurrentHealth + Regen);
		return;
	}

	if (Data.EvaluatedData.Attribute == GetManaRegenAttribute())
	{
		const int Regen = GetManaRegen();
		SetManaRegen(0);
		const int CurrentValue = GetMana();
		SetMana(CurrentValue + Regen);
		return;
	}

	if (Data.EvaluatedData.Attribute == GetStaminaRegenAttribute())
	{
		const int Regen = GetStaminaRegen();
		SetStaminaRegen(0);
		const int CurrentValue = GetStamina();
		SetStamina(CurrentValue + Regen);
	}
}
