#include "Tests/AttackFightingEnemy.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "MMOPlayerState.h"
#include "Tags.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"

void AAttackFightingEnemy::PrepareTest()
{
	Super::PrepareTest();

	if (!Attacker)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker not setuped");
		return;
	}

	if (!Attacker2)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker2 not setuped");
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


	if (!Attacker->GetPlayerState())
	{
		AMMOPlayerState* playerstate = GetWorld()->SpawnActor<AMMOPlayerState>(PlayerStateToSpawn);

		Attacker->SetPlayerState(playerstate);
		Attacker->SetOwner(playerstate);
	}

	if (!Attacker2->GetPlayerState())
	{
		AMMOPlayerState* playerstate = GetWorld()->SpawnActor<AMMOPlayerState>(PlayerStateToSpawn);

		Attacker2->SetPlayerState(playerstate);
		Attacker2->SetOwner(playerstate);
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

	if (!Attacker2->GetController())
	{
		AAIController* controller = GetWorld()->SpawnActor<AAIController>(Attacker2->AIControllerClass);
		controller->Possess(Attacker2);
	}

	Defender->Interact(EInteractType::Attack, Attacker);
}

void AAttackFightingEnemy::StartTest()
{
	Super::StartTest();

	Defender->Interact(EInteractType::Attack, Attacker2);

	if (Attacker2->GetAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Battle))
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker2 cant attack enemy in battle");
		return;
	}

	FinishTest(EFunctionalTestResult::Succeeded, "Valid");
}

void AAttackFightingEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
