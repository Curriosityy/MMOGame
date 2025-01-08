#include "GameState/InGameGameState.h"

#include "AbilitySystemComponent.h"
#include "DebugHelper.h"
#include "MMOGameInstance.h"
#include "Tags.h"
#include "BattleSystem/Battle.h"
#include "BattleSystem/BattleBoard.h"
#include "BattleSystem/BattleBoardManager.h"
#include "BattleSystem/BattleComponent.h"
#include "BattleSystem/BattleManager.h"
#include "Character/MMORPGCharacter.h"
#include "Controllers/PlayerGameController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

AInGameGameState::AInGameGameState()
{
	SetReplicates(true);
}

void AInGameGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	if (HasAuthority())
	{
		SetMatchState(MatchState::InProgress);
	}
}

bool AInGameGameState::IsValidBattle(AMMORPGCharacter* Attacker, AMMORPGCharacter* Defender)
{
	if (Attacker == Defender ||
		!Attacker ||
		!Defender)
	{
		return false;
	}

	return true;
}

void AInGameGameState::TryInteract(EInteractType Interaction, AActor* InteractWith, AMMORPGCharacter* Interactor)
{
	if (!HasAuthority())
	{
		return;
	}

	if (InteractWith == Interactor ||
		!InteractWith ||
		!Interactor)
	{
		return;
	}

	Debug::Print(FString::Printf(
		             TEXT("AInGameGameState::TryInteract Local role = %s"),
		             *UEnum::GetValueAsName(GetLocalRole()).ToString()), this);

	switch (Interaction)
	{
	case EInteractType::None:
		return;
		break;
	case EInteractType::Attack:
		if (!IsValidBattle(Interactor, Cast<AMMORPGCharacter>(InteractWith)))
		{
			return;
		}
		Attack(Interactor, Cast<AMMORPGCharacter>(InteractWith));
		break;
	case EInteractType::Pickup:
		Debug::Print(TEXT("EInteractionType::Pickup is not implemented, AInGameGameState::TryInteract"), this);
		break;
	case EInteractType::Trade:
		Debug::Print(TEXT("EInteractionType::Trade is not implemented, AInGameGameState::TryInteract"), this);
		break;
	case EInteractType::Party:
		Debug::Print(TEXT("EInteractionType::Party is not implemented, AInGameGameState::TryInteract"), this);
		break;
	}
}

void AInGameGameState::Attack(AMMORPGCharacter* Attacker, AMMORPGCharacter* Defender)
{
	check(Attacker)
	check(Defender)

	check(BattleGameplayEffect)

	if (Attacker->GetAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Battle))
	{
		return;
	}

	if (Defender->GetAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Battle))
	{
		return;
	}


	const FString AttackerName = Cast<APlayerGameController>(Attacker->GetController())
		                             ? Cast<APlayerGameController>(Attacker->GetController())->GetPlayerName()
		                             : Attacker->GetName();

	const FString DefenderName = Cast<APlayerGameController>(Defender->GetController())
		                             ? Cast<APlayerGameController>(Defender->GetController())->GetPlayerName()
		                             : Defender->GetName();
	Debug::Print(FString::Printf(
		             TEXT("AInGameGameState::Attack_Implementation Attacker %s Defender %s"), *AttackerName,
		             *DefenderName), this);

	Debug::Print(FString::Printf(
		             TEXT("AInGameGameState::Attack_Implementation Attacker %s Defender %s"),
		             *UEnum::GetValueAsString(Attacker->GetLocalRole()),
		             *UEnum::GetValueAsString(Defender->GetLocalRole())), this);

	if (!BattleBoardManager.IsValid())
	{
		TArray<AActor*> BBManager;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABattleBoardManager::StaticClass(), BBManager);
		BattleBoardManager = Cast<ABattleBoardManager>(BBManager[0]);
	}

	if (!BattleManager.IsValid())
	{
		TArray<AActor*> BBManager;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABattleManager::StaticClass(), BBManager);
		BattleManager = Cast<ABattleManager>(BBManager[0]);
	}

	auto attackers = {Attacker->GetBattleComponent()};
	auto defenders = {Defender->GetBattleComponent()};

	FGameplayEffectContextHandle ContextHandle;

	// for (UBattleComponent* att : attackers)
	// {
	// 	UAbilitySystemComponent* acs = Cast<IAbilitySystemInterface>(att->GetOwner())->GetAbilitySystemComponent();
	// 	acs->ApplyGameplayEffectToSelf(BattleGameplayEffect.GetDefaultObject(), 1, acs->MakeEffectContext());
	// }
	//
	// for (UBattleComponent* deff : defenders)
	// {
	// 	UAbilitySystemComponent* acs = Cast<IAbilitySystemInterface>(deff->GetOwner())->GetAbilitySystemComponent();
	// 	acs->ApplyGameplayEffectToSelf(BattleGameplayEffect.GetDefaultObject(), 1, acs->MakeEffectContext());
	// }

	ABattleBoard* Board = BattleBoardManager->GetBoardFromPool();
	UBattle* Battle = NewObject<UBattle>(GetWorld());

	Battle->StartBattle(Board, attackers, defenders);
	BattleManager->AddBattle(Battle);
}
