#include "MMOPlayerState.h"

#include "DebugHelper.h"
#include "Tags.h"
#include "AbilitySystem/MMOPlayerAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "BattleSystem/BattleComponent.h"
#include "Controllers/PlayerGameController.h"
#include "DataAsset/AbilityDataAsset.h"
#include "DataAsset/AbilityStartupDataAsset.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

AMMOPlayerState::AMMOPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMMOPlayerAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>("AttributeSet");

	BattleComponent = CreateDefaultSubobject<UBattleComponent>("BattleComponent");
}

void AMMOPlayerState::TryBindNewAbility(FGameplayAbilitySpec* SpecToCheck) const
{
	for (const FBindingStruct& Bindings : BattleAbilityBinding->Bindings)
	{
		if (SpecToCheck->Ability.GetClass() == Bindings.Ability)
		{
			Cast<UMMOPlayerAbilitySystemComponent>(GetAbilitySystemComponent())
				->BindBattleAbilityToShortcut(Bindings.Ability, Bindings.InputTag);

			break;
		}
	}
}

void AMMOPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAuthority())
	{
		Cast<UMMOPlayerAbilitySystemComponent>(GetAbilitySystemComponent())->OnAbilityGranted.AddUObject(
			this, &ThisClass::TryBindNewAbility);

		if (BattleAbilityBinding)
		{
			for (const FBindingStruct& Bindings : BattleAbilityBinding->Bindings)
			{
				Cast<UMMOPlayerAbilitySystemComponent>(GetAbilitySystemComponent())
					->BindBattleAbilityToShortcut(Bindings.Ability, Bindings.InputTag);
			}
		}

		return;
	}

	UAbilityStartupDataAsset* LoadedData = PlayerSpecificData.LoadSynchronous();

	checkf(LoadedData, TEXT("AARPGHeroCharacter::PossessedBy: Failed to load CharacterStartupData"));
	LoadedData->GiveToASC(GetAbilitySystemComponent());
}

UAbilitySystemComponent* AMMOPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBattleComponent* AMMOPlayerState::GetBattleComponent() const
{
	return BattleComponent;
}


void AMMOPlayerState::Setup(const FFullCharInfo& FullCharInfo)
{
	AttributeSet->InitStrength(FullCharInfo.CharacterData.Strength);
	AttributeSet->InitDexterity(FullCharInfo.CharacterData.Dexterity);
	AttributeSet->InitIntelligence(FullCharInfo.CharacterData.Intelligence);
	AttributeSet->InitWisdom(FullCharInfo.CharacterData.Wisdom);
	AttributeSet->InitFaith(FullCharInfo.CharacterData.Faith);
	AttributeSet->InitCharisma(FullCharInfo.CharacterData.Charisma);

	AttributeSet->InitHealth(FullCharInfo.CharacterData.Health);
	AttributeSet->InitMaxHealth(FullCharInfo.CharacterData.MaxHealth);

	AttributeSet->InitMana(FullCharInfo.CharacterData.Mana);
	AttributeSet->InitMaxMana(FullCharInfo.CharacterData.MaxMana);

	AttributeSet->InitMaxStamina(FullCharInfo.CharacterData.MaxStamina);
	AttributeSet->InitStamina(FullCharInfo.CharacterData.Stamina);

	AttributeSet->InitLevel(FullCharInfo.CharacterData.CharacterLevel);
	AttributeSet->InitExp(FullCharInfo.CharacterData.Exp);

	AttributeSet->InitMaxAbilityPoints(FullCharInfo.CharacterData.MaxAbilityPoints);
	AttributeSet->InitCurrentAbilityPoints(FullCharInfo.CharacterData.MaxAbilityPoints);


	SetPlayerName(FullCharInfo.CharacterData.CharacterName);
}

void AMMOPlayerState::HandleWelcomeMessage()
{
	if (!bHasBeenWelcomed)
	{
		//Nickname received
		// Debug::Print(FString::Printf(TEXT("Nickname received %s, old nick %s"), *GetPlayerName(), *GetOldPlayerName()),
		//              this);
	}
	Super::HandleWelcomeMessage();
}

void AMMOPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();
}

FString AMMOPlayerState::GetHumanReadableName() const
{
	return Super::GetHumanReadableName();
}

ETeamAttitude::Type AMMOPlayerState::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	if (&Other == this)
	{
		return ETeamAttitude::Friendly;
	}

	if (GetGenericTeamId() == FGenericTeamId::NoTeam)
	{
		return ETeamAttitude::Hostile;
	}

	return IGenericTeamAgentInterface::GetTeamAttitudeTowards(Other);
}

EInteractType AMMOPlayerState::GetInteractionType()
{
	return EInteractType::Attack;
}

AActor* AMMOPlayerState::GetActor()
{
	return GetPawn();
}
