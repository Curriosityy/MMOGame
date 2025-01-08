#include "Tests/BattleTurnTest.h"

#include "AIController.h"
#include "MMOPlayerState.h"
#include "BattleSystem/Battle.h"
#include "BattleSystem/BattleManager.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"

void ABattleTurnTest::PrepareTest()
{
	Super::PrepareTest();


	if (!Attacker)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker not setuped");
		return;
	}

	if (!Defender)
	{
		FinishTest(EFunctionalTestResult::Error, "Defender not setuped");
		return;
	}

	if (!PlayerStateToSpawn.Get())
	{
		FinishTest(EFunctionalTestResult::Error, "PlayerStateToSpawn not setuped");
		return;
	}

	if (!BattleManager.Get())
	{
		FinishTest(EFunctionalTestResult::Error, "PlayerStateToSpawn not setuped");
		return;
	}

	if (!Attacker->GetPlayerState())
	{
		AMMOPlayerState* playerstate = GetWorld()->SpawnActor<AMMOPlayerState>(PlayerStateToSpawn);

		Attacker->SetPlayerState(playerstate);
		Attacker->SetOwner(playerstate);
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
	Battle = BattleManager->FindBattle(Attacker);


	if (!Battle.Get())
	{
		FinishTest(EFunctionalTestResult::Error, "Battle not spawned");
		return;
	}

	StartTurnOwner = Battle->GetCurrentTurnOwner();
}

void ABattleTurnTest::StartTest()
{
	Super::StartTest();
}

void ABattleTurnTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (StartTurnOwner != Battle->GetCurrentTurnOwner())
	{
		FinishTest(EFunctionalTestResult::Succeeded, "Battle turn swapped");
	}
}
