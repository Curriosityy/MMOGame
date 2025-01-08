#include "Tests/SpawnOnBattleBoardTest.h"

#include "AIController.h"
#include "DebugHelper.h"
#include "MMOPlayerState.h"
#include "BattleSystem/BattleBoard.h"
#include "BattleSystem/BattleBoardManager.h"
#include "BattleSystem/BattleComponent.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"

void ASpawnOnBattleBoardTest::PrepareTest()
{
	Super::PrepareTest();


	if (!Attacker->GetPlayerState())
	{
		if (!PlayerStateToSpawn)
		{
			FinishTest(EFunctionalTestResult::Error, "PlayerStateToSpawn not setuped");
		}

		AMMOPlayerState* playerstate = GetWorld()->SpawnActor<AMMOPlayerState>(PlayerStateToSpawn);

		Attacker->SetPlayerState(playerstate);
		Attacker->SetOwner(playerstate);
	}


	if (!Defender)
	{
		FinishTest(EFunctionalTestResult::Error, "Defender not setuped");
	}

	if (!BattleBoardManager)
	{
		FinishTest(EFunctionalTestResult::Error, "BattleBoardManager not setuped");
	}

	BattleBoard = BattleBoardManager->PeekBoardFromPool();

	if (!BattleBoard)
	{
		FinishTest(EFunctionalTestResult::Error, "BattleBoard not setuped");
	}

	if (!Attacker)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker not setuped");
	}


	if (!Defender->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Defender->AIControllerClass);
		controller->Possess(Defender);
	}

	if (!Attacker->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Attacker->AIControllerClass);
		controller->Possess(Attacker);
	}

	Defender->Interact(EInteractType::Attack, Attacker);

	Debug::Print("ABattleFunctionalTest::PrepareTest", this);
}

void ASpawnOnBattleBoardTest::StartTest()
{
	Super::StartTest();
}

void ASpawnOnBattleBoardTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FTransform Place1 = BattleBoard->GetSpawnPlace(Team1, 0);
	Place1.SetLocation({Place1.GetLocation().X, Place1.GetLocation().Y, 0});
	FTransform Place2 = BattleBoard->GetSpawnPlace(Team2, 0);
	Place2.SetLocation({Place2.GetLocation().X, Place2.GetLocation().Y, 0});
	FTransform CharPlace1 = Attacker->GetBattleComponent()->BattleCharacter->GetActorTransform();
	CharPlace1.SetLocation({CharPlace1.GetLocation().X, CharPlace1.GetLocation().Y, 0});
	FTransform CharPlace2 = Defender->GetBattleComponent()->BattleCharacter->GetActorTransform();
	CharPlace2.SetLocation({CharPlace2.GetLocation().X, CharPlace2.GetLocation().Y, 0});

	if (!Place1.Equals(CharPlace1))
	{
		return;
	}

	if (!Place2.Equals(CharPlace2))
	{
		return;
	}

	FinishTest(EFunctionalTestResult::Succeeded, "Valid Battleboard");
}
