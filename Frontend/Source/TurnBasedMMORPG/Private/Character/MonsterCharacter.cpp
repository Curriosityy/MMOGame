// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MonsterCharacter.h"

#include "AbilitySystemComponent.h"
#include "AboveHeadUserWidget.h"
#include "Tags.h"
#include "AbilitySystem/MMOAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "AbilitySystem/Attribute/MonsterAttributeSet.h"
#include "BattleSystem/BattleComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/AbilityStartupDataAsset.h"
#include "DataAsset/EnemyInfoTableRow.h"
#include "Engine/AssetManager.h"
#include "Net/UnrealNetwork.h"

AMonsterCharacter::AMonsterCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMMOAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>("AttributeSet");

	BattleComponent = CreateDefaultSubobject<UBattleComponent>("BattleComponent");
	BattleComponent->SetIsReplicated(true);
}

void AMonsterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	AboveHeadWidget->InitWidget();
	Cast<UAboveHeadUserWidget>(AboveHeadWidget->GetWidget())->SetOwningActor(this);


	const FEnemyInfoTableRow* MonsterData = MonsterDataInfo.GetRow<FEnemyInfoTableRow>("");

	checkf(MonsterData, TEXT("MonsterData not found %s"), *GetPathName(this));

	if (!GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(
		MMOGameplayTags::Shared_Status_AbilityGranted.GetTag().GetSingleTagContainer()))
	{
		for (const FAbilityDataInfoRow& Ability : MonsterData->Abilities)
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(
				Ability.Ability.ToSoftObjectPath(),
				[Ability,this]()
				{
					const TSubclassOf<UGameplayAbility> LoadedData = Ability.Ability.Get();

					if (!LoadedData)
					{
						return;
					}

					FGameplayAbilitySpec Spec{LoadedData};
					Spec.SourceObject = AbilitySystemComponent->GetAvatarActor();
					Spec.Level = Ability.AbilityLevel;
					AbilitySystemComponent->GiveAbility(Spec);
				});
		}
	}

	AttributeSet->InitStrength(MonsterData->Strength);
	AttributeSet->InitDexterity(MonsterData->Dexterity);
	AttributeSet->InitIntelligence(MonsterData->Intelligence);
	AttributeSet->InitWisdom(MonsterData->Wisdom);
	AttributeSet->InitFaith(MonsterData->Faith);
	AttributeSet->InitCharisma(MonsterData->Charisma);

	AttributeSet->InitCharisma(MonsterData->Armour);

	AttributeSet->InitMaxHealth(MonsterData->MaxHealth);
	AttributeSet->InitHealth(MonsterData->MaxHealth);

	AttributeSet->InitMaxMana(MonsterData->MaxMana);
	AttributeSet->InitMana(MonsterData->MaxMana);

	AttributeSet->InitMaxStamina(MonsterData->MaxStamina);
	AttributeSet->InitStamina(MonsterData->MaxStamina);

	AttributeSet->InitLevel(MonsterData->Level);

	AttributeSet->InitMaxAbilityPoints(MonsterData->MaxAbilityPoints);
	AttributeSet->InitCurrentAbilityPoints(MonsterData->MaxAbilityPoints);

	GetAbilitySystemComponent()->AddLooseGameplayTag(MMOGameplayTags::Shared_Status_AbilityGranted);
}

EInteractType AMonsterCharacter::GetInteractionType()
{
	return EInteractType::Attack;
}

UAbilitySystemComponent* AMonsterCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBattleComponent* AMonsterCharacter::GetBattleComponent() const
{
	return BattleComponent;
}

FString AMonsterCharacter::GetHumanReadableName() const
{
	return MonsterName;
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	AboveHeadWidget->InitWidget();
	Cast<UAboveHeadUserWidget>(AboveHeadWidget->GetWidget())->SetOwningActor(this);
}

void AMonsterCharacter::Rep_Name(const FString& OldName)
{
}

void AMonsterCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, MonsterName);
}
