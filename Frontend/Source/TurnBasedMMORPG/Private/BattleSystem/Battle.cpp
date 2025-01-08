#include "BattleSystem/Battle.h"

#include "AbilitySystemComponent.h"
#include "DebugHelper.h"
#include "EditorCategoryUtils.h"
#include "Tags.h"
#include "TimerManager.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "BattleSystem/BattleBoard.h"
#include "BattleSystem/BattleComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Character/MMORPGCharacter.h"
#include "Controllers/PlayerGameController.h"
#include "Engine/World.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"

int UBattle::CalculateInitiative(const UAbilitySystemComponent* ASC)
{
	const int Strength = ASC->GetNumericAttribute(UBaseAttributeSet::GetStrengthAttribute());
	const int Dexterity = ASC->GetNumericAttribute(UBaseAttributeSet::GetDexterityAttribute());
	const int Intelligence = ASC->GetNumericAttribute(UBaseAttributeSet::GetIntelligenceAttribute());
	const int Wisdom = ASC->GetNumericAttribute(UBaseAttributeSet::GetWisdomAttribute());
	const int Faith = ASC->GetNumericAttribute(UBaseAttributeSet::GetFaithAttribute());
	const int Charisma = ASC->GetNumericAttribute(UBaseAttributeSet::GetCharismaAttribute());


	return UKismetMathLibrary::RandomInteger(1) + Strength / 7 + Dexterity / 2 + Intelligence / 4 + Wisdom / 5 +
		Faith / 6 + Charisma / 3;
}

void UBattle::RollBattleQueue()
{
	TArray<UBattleComponent*> cpQueue = BattleQueue;
	TArray<int> InitList = {0};
	InitList.Empty();
	BattleQueue.Empty(cpQueue.Num());

	for (UBattleComponent* Player : cpQueue)
	{
		int Init = CalculateInitiative(
			Cast<IAbilitySystemInterface>(Player->GetOwner())->GetAbilitySystemComponent());
		InitList.Add(Init);
	}

	int32 index;
	for (int i = 0; i < cpQueue.Num(); i++)
	{
		FMath::Max(InitList, &index);
		InitList[index] = -1;
		BattleQueue.AddUnique(cpQueue[index]);
	}

	check(BattleQueue.Num() == cpQueue.Num());
}

void UBattle::StartNewTurn()
{
	CurrentTurnComponent = BattleQueue[currentTurnIndex];
	Cast<IAbilitySystemInterface>(CurrentTurnComponent->GetOwner())->GetAbilitySystemComponent()->
	                                                                 AddLooseGameplayTag(
		                                                                 MMOGameplayTags::Shared_Status_CurrentTurn);
	Cast<IAbilitySystemInterface>(CurrentTurnComponent->GetOwner())->GetAbilitySystemComponent()->
	                                                                 AddReplicatedLooseGameplayTag(
		                                                                 MMOGameplayTags::Shared_Status_CurrentTurn);

	CurrentTurnComponent->StartRound();
}

AMMORPGCharacter* UBattle::GetCurrentTurnOwner()
{
	return Cast<AMMORPGCharacter>(CurrentTurnComponent->GetPawn());
}

void UBattle::OnTurnEnd(UBattleComponent* Sender)
{
	if (Sender == CurrentTurnComponent)
	{
		UAbilitySystemComponent* asc = Cast<IAbilitySystemInterface>(CurrentTurnComponent->GetOwner())->
			GetAbilitySystemComponent();
		TArray<FGameplayAbilitySpec*> Specs;
		asc->GetActivatableGameplayAbilitySpecsByAllMatchingTags(
			MMOGameplayTags::Shared_Ability_PlayQueue.GetTag().GetSingleTagContainer(), Specs);

		checkf(Specs.Num() > 0, TEXT("%s has no ability Shared_Ability_PlayQueue"), *GetOuter()->GetName());
		checkf(Specs.Num() < 2, TEXT("%s has multiple ability Shared_Ability_PlayQueue"), *GetOuter()->GetName());


		asc->OnAbilityEnded.AddLambda([this,Specs,asc](const FAbilityEndedData& AbilityEndedData)
		{
			if (AbilityEndedData.AbilityThatEnded.GetClass() != Specs[0]->Ability.GetClass())
			{
				return;
			}

			asc->RemoveLooseGameplayTag(MMOGameplayTags::Shared_Status_CurrentTurn);
			asc->RemoveReplicatedLooseGameplayTag(MMOGameplayTags::Shared_Status_CurrentTurn);

			currentTurnIndex = ++currentTurnIndex % BattleQueue.Num();
			StartNewTurn();
			asc->OnAbilityEnded.RemoveAll(this);
		});

		asc->TryActivateAbility(Specs[0]->Handle);
	}
}

void UBattle::SetupIfPlayer(const UBattleComponent* BattleComponent)
{
	const APlayerState* PlayerState = Cast<APlayerState>(BattleComponent->GetOwner());

	if (PlayerState && PlayerState->GetPlayerController())
	{
		APlayerGameController* PC = Cast<APlayerGameController>(PlayerState->GetPlayerController());
		PC->SetupBattleInput(false);
		PC->SetupBattleHUD(true);
		PC->LoadScreen(true);
	}
}

AMMORPGCharacter* UBattle::GetPawn(const UBattleComponent* BattleComponent)
{
	AMMORPGCharacter* Pawn = Cast<AMMORPGCharacter>(BattleComponent->GetOwner());

	if (!Pawn)
	{
		Pawn = Cast<APlayerState>(BattleComponent->GetOwner())->GetPawn<AMMORPGCharacter>();
	}

	return Pawn;
}

void UBattle::StartBattle(ABattleBoard* BBoard, const TArray<UBattleComponent*>& Attackers,
                          const TArray<UBattleComponent*>& Defenders)
{
	Debug::Print("UBattle::StartBattle ", this);
	Team1Players = {};
	Team2Players = {};
	BattleBoard = BBoard;

	int ite = 0;
	//ZIP ATTACKER AND DEFENDER ? 
	for (UBattleComponent* Attacker : Attackers)
	{
		SetupIfPlayer(Attacker);


		AMMORPGCharacter* Pawn = GetPawn(Attacker);


		Pawn->GetMovementComponent()->StopMovementImmediately();
		FTransform SpawnLocation = BattleBoard->GetSpawnPlace(Team1, ite++);

		AMMORPGCharacter* BattleActor = GetWorld()->SpawnActorDeferred<AMMORPGCharacter>(Pawn->GetClass(),
			SpawnLocation,
			Pawn->GetOwner(),
			Pawn,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
			ESpawnActorScaleMethod::OverrideRootScale);

		BattleActor->SetPlayerState(Pawn->GetPlayerState());

		BattleActor->GetBattleComponent()->BattleCharacter = BattleActor;
		BattleActor->GetBattleComponent()->WorldCharacter = Pawn;
		Pawn->GetBattleComponent()->BattleCharacter = BattleActor;
		Pawn->GetBattleComponent()->WorldCharacter = Pawn;

		BattleActor->FinishSpawning(SpawnLocation);

		Pawn->GetController()->Possess(BattleActor);

		UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(Pawn->GetAbilitySystemComponent(),
		                                                              MMOGameplayTags::Shared_Status_Battle);
		UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(BattleActor->GetAbilitySystemComponent(),
		                                                              MMOGameplayTags::Shared_Status_Battle);

		BattleActor->GetBattleComponent()->StartLocation = SpawnLocation;
		Team1Players.Add(BattleActor->GetBattleComponent());
		BattleActor->GetBattleComponent()->OnTurnEnd.AddDynamic(this, &ThisClass::OnTurnEnd);
	}

	ite = 0;
	for (UBattleComponent* Defender : Defenders)
	{
		SetupIfPlayer(Defender);

		AMMORPGCharacter* Pawn = GetPawn(Defender);

		Pawn->GetMovementComponent()->StopMovementImmediately();
		FTransform SpawnLocation = BattleBoard->GetSpawnPlace(Team2, ite++);

		AMMORPGCharacter* BattleActor = GetWorld()->SpawnActorDeferred<AMMORPGCharacter>(Pawn->GetClass(),
			SpawnLocation,
			Pawn->GetOwner(),
			Pawn,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
			ESpawnActorScaleMethod::OverrideRootScale);

		BattleActor->SetPlayerState(Pawn->GetPlayerState());

		BattleActor->GetBattleComponent()->BattleCharacter = BattleActor;
		BattleActor->GetBattleComponent()->WorldCharacter = Pawn;
		Pawn->GetBattleComponent()->BattleCharacter = BattleActor;
		Pawn->GetBattleComponent()->WorldCharacter = Pawn;

		BattleActor->FinishSpawning(SpawnLocation);

		Pawn->GetController()->Possess(BattleActor);


		UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(Pawn->GetAbilitySystemComponent(),
		                                                              MMOGameplayTags::Shared_Status_Battle);
		UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(BattleActor->GetAbilitySystemComponent(),
		                                                              MMOGameplayTags::Shared_Status_Battle);

		Team2Players.Add(BattleActor->GetBattleComponent());
		BattleActor->GetBattleComponent()->OnTurnEnd.AddDynamic(this, &ThisClass::OnTurnEnd);
	}

	for (UBattleComponent* Team1Player : Team1Players)
	{
		Team1Player->SetTarget(Team1Player);
		Team1Player->SetTarget(Team2Players[0]);
	}

	for (UBattleComponent* Team2Player : Team2Players)
	{
		Team2Player->SetTarget(Team2Player);
		Team2Player->SetTarget(Team1Players[0]);
	}

	//TODO Ensure that every client loaded everything
	//battle board loaded,
	//All client spawned ect.
	//OnSpawnEvent?
	BattleQueue.Append(Team1Players);
	BattleQueue.Append(Team2Players);
	RollBattleQueue();
	currentTurnIndex = 0;
	StartNewTurn();
}

void UBattle::SimulateBattle()
{
	Debug::Print("UBattle::SimulateBattle ", this);
	//TODO Simulate battle
	EndSimualtionBattle();
}

void UBattle::EndSimualtionBattle()
{
	Debug::Print("UBattle::EndSimulationBattle ", this);
	StartNewTurn();
}

void UBattle::BeginDestroy()
{
	UObject::BeginDestroy();
}

TArray<UBattleComponent*> UBattle::GetPlayers() const
{
	TArray<UBattleComponent*> Result;
	Result.Append(Team1Players);
	Result.Append(Team2Players);
	return Result;
}
