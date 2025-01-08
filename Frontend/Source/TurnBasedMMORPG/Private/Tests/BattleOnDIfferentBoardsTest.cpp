#include "Tests/BattleOnDIfferentBoardsTest.h"

#include "AIController.h"
#include "MMOPlayerState.h"
#include "BattleSystem/BattleBoardManager.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"

class AAIController;

void ABattleOnDIfferentBoardsTest::PrepareTest()
{
	Super::PrepareTest();

	if (!Attacker1 || !Attacker2 || Attacker1 == Attacker2)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker not setuped");
		return;
	}

	if (!BattleBoardManager)
	{
		FinishTest(EFunctionalTestResult::Error, "BattleBoardManager not setuped");
		return;
	}

	if (!Defender1 || !Defender2 || Defender1 == Defender2)
	{
		FinishTest(EFunctionalTestResult::Error, "Defender not setuped");
		return;
	}

	if (!PlayerStateToSpawn.Get())
	{
		FinishTest(EFunctionalTestResult::Error, "PlayerStateToSpawn not setuped");
		return;
	}

	if (!Attacker1->GetPlayerState())
	{
		AMMOPlayerState* playerstate = GetWorld()->SpawnActor<AMMOPlayerState>(PlayerStateToSpawn);

		Attacker1->SetPlayerState(playerstate);
		Attacker1->SetOwner(playerstate);
	}

	if (!Attacker2->GetPlayerState())
	{
		AMMOPlayerState* playerstate = GetWorld()->SpawnActor<AMMOPlayerState>(PlayerStateToSpawn);

		Attacker2->SetPlayerState(playerstate);
		Attacker2->SetOwner(playerstate);
	}

	if (!Defender1->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Defender1->AIControllerClass);
		controller->Possess(Defender1);
	}

	if (!Defender2->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Defender2->AIControllerClass);
		controller->Possess(Defender2);
	}

	if (!Attacker1->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Attacker1->AIControllerClass);
		controller->Possess(Attacker1);
	}

	if (!Attacker2->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Attacker2->AIControllerClass);
		controller->Possess(Attacker2);
	}
}

void ABattleOnDIfferentBoardsTest::StartTest()
{
	Super::StartTest();
	auto firstBB = BattleBoardManager->PeekBoardFromPool();
	Defender1->Interact(EInteractType::Attack, Attacker1);
	auto secBB = BattleBoardManager->PeekBoardFromPool();
	Defender2->Interact(EInteractType::Attack, Attacker2);

	if (firstBB == secBB ||
		firstBB == BattleBoardManager->PeekBoardFromPool() ||
		secBB == BattleBoardManager->PeekBoardFromPool())
	{
		FinishTest(EFunctionalTestResult::Error, "Battle should not be on same board");
		return;
	}

	FinishTest(EFunctionalTestResult::Succeeded, "");
}
