#include "Tests/EndTurnAbilityTest.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "MMOPlayerState.h"
#include "AbilitySystem/MMOAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBaseGameplayAbility.h"
#include "BattleSystem/Battle.h"
#include "BattleSystem/BattleManager.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"

void AEndTurnAbilityTest::PrepareTest()
{
	Super::PrepareTest();

	if (Attacker)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker nullptr");
		return;
	}

	if (Defender)
	{
		FinishTest(EFunctionalTestResult::Error, "Defender nullptr");
		return;
	}

	if (PlayerStateToSpawn.Get() == nullptr)
	{
		FinishTest(EFunctionalTestResult::Error, "PlayerStateToSpawn nullptr");
		return;
	}

	if (EndTurnAbility.Get() == nullptr)
	{
		FinishTest(EFunctionalTestResult::Error, "EndTurnAbility nullptr");
		return;
	}

	if (BattleManager.Get() == nullptr)
	{
		FinishTest(EFunctionalTestResult::Error, "EndTurnAbility nullptr");
		return;
	}	

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

	if(Cast<UMMOAbilitySystemComponent>(Attacker->GetAbilitySystemComponent())->GetActivatableAbilityIndexBasedOnClass(EndTurnAbility)<0)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker don't have EndTurnAbility");
		return;
	}

	if(Cast<UMMOAbilitySystemComponent>(Defender->GetAbilitySystemComponent())->GetActivatableAbilityIndexBasedOnClass(EndTurnAbility)<0)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker don't have EndTurnAbility");
		return;
	}

	Defender->Interact(EInteractType::Attack, Attacker);
	Battle = BattleManager->FindBattle(Attacker);
	
	if(!Battle.IsValid())
	{
		FinishTest(EFunctionalTestResult::Error, "Battle is invalid");
		return;
	}
	StartTurnOwner = Battle->GetCurrentTurnOwner();
	
	if(!StartTurnOwner.IsValid())
	{
		FinishTest(EFunctionalTestResult::Error, "StartTurnOwner is invalid");
		return;
	}
}

void AEndTurnAbilityTest::StartTest()
{
	Super::StartTest();
	
	if(StartTurnOwner->GetAbilitySystemComponent()->TryActivateAbilityByClass(EndTurnAbility))
	{
		FinishTest(EFunctionalTestResult::Error, "Ability activation failed "+Battle->GetCurrentTurnOwner()->GetFullName());
		return;
	}

	if(Battle->GetCurrentTurnOwner() == StartTurnOwner)
	{
		FinishTest(EFunctionalTestResult::Error, "Turn has not changed");
		return;
	}

	
	FinishTest(EFunctionalTestResult::Succeeded,"");
}
