// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "MMOPlayerState.h"
#include "Tags.h"
#include "AbilitySystem/MMOPlayerAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/AbilityDataAsset.h"
#include "DataAsset/AbilityStartupDataAsset.h"
#include "DataAsset/ClassSpecificDataAsset.h"
#include "Engine/AssetManager.h"
#include "GameFramework/PlayerState.h"
#include "UI/InGameHUD.h"
#include "UI/MMOBaseWidget.h"


APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UMMOPlayerAbilitySystemComponent>("AbilitySystemComponent"))
{
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller.
	Super::PossessedBy(NewController);
	SetOwner(NewController);

	if (!HasAuthority())
	{
		return;
	}

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	MainPlayerState = Cast<AMMOPlayerState>(GetPlayerState());

	for (TSoftClassPtr<UMMOBattleAbility>& Ability : ClassSpecificAsset->Abilities)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			Ability.ToSoftObjectPath(),
			[this,Ability]()
			{
				auto LoadedData = Ability.Get();
				if (!LoadedData)
				{
					return;
				}


				FGameplayAbilitySpec Spec{LoadedData};
				Spec.SourceObject = GetAbilitySystemComponent()->GetAvatarActor();
				Spec.Level = 1; //TODO: Get from DB
				GetAbilitySystemComponent()->GiveAbility(Spec);
			});
	}

	GetAbilitySystemComponent()->AddLooseGameplayTag(MMOGameplayTags::Shared_Status_AbilityGranted);
}


UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return GetPlayerState()
		       ? Cast<IAbilitySystemInterface>(GetPlayerState())->GetAbilitySystemComponent()
		       : Cast<IAbilitySystemInterface>(MainPlayerState)->GetAbilitySystemComponent();
}

UBattleComponent* APlayerCharacter::GetBattleComponent() const
{
	return GetPlayerState()
		       ? Cast<IBattleComponentInterface>(GetPlayerState())->GetBattleComponent()
		       : Cast<IBattleComponentInterface>(MainPlayerState)->GetBattleComponent();
}

void APlayerCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	ScaleValue = GetAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Battle)
		             ? 0
		             : ScaleValue;
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (GetPlayerState())
	{
		GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
		MainPlayerState = Cast<AMMOPlayerState>(GetPlayerState());
		AboveHeadWidget->InitWidget();
		Cast<UMMOBaseWidget>(AboveHeadWidget->GetWidget())->SetOwningActor(Cast<AMMOPlayerState>(GetPlayerState()));
	}


	// Set the ASC for clients. Server does this in PossessedBy.

	// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.

	//Set to not lose when changing pawn
}

FGenericTeamId APlayerCharacter::GetGenericTeamId() const
{
	return GetPlayerState()
		       ? Cast<IGenericTeamAgentInterface>(GetPlayerState())->GetGenericTeamId()
		       : Cast<IGenericTeamAgentInterface>(MainPlayerState)->GetGenericTeamId();
}

ETeamAttitude::Type APlayerCharacter::GetTeamAttitudeTowards(const AActor& Other) const
{
	return GetPlayerState()
		       ? Cast<IGenericTeamAgentInterface>(GetPlayerState())->GetTeamAttitudeTowards(Other)
		       : Cast<IGenericTeamAgentInterface>(MainPlayerState)->GetTeamAttitudeTowards(Other);
}

void APlayerCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	GetPlayerState()
		? Cast<IGenericTeamAgentInterface>(GetPlayerState())->SetGenericTeamId(TeamID)
		: Cast<IGenericTeamAgentInterface>(MainPlayerState)->SetGenericTeamId(TeamID);
}

void APlayerCharacter::InitAbove()
{
	if (!AboveHeadWidget->GetWidget())
	{
		AboveHeadWidget->InitWidget();
	}
	//Play join animation here
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
	}
}
