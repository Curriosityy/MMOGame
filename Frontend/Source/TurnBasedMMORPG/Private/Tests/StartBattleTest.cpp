// 


#include "Tests/StartBattleTest.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "DebugHelper.h"
#include "MMOPlayerState.h"
#include "Tags.h"
#include "AI/AISystemBase.h"
#include "BattleSystem/BattleComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/MMORPGCharacter.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AStartBattleTest::AStartBattleTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStartBattleTest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStartBattleTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStartBattleTest::StartTest()
{
	Super::StartTest();
	Debug::Print("ABattleFunctionalTest::StartTest", this);

	Defender->Interact(EInteractType::Attack, Attacker);

	if (!AssertTrue(
		Defender->GetAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Battle),
		"Defender should have Status_Battle"))
	{
		FinishTest(EFunctionalTestResult::Error, "Defender should have Status_Battle");
		return;
	}
	if (!AssertTrue(
		Attacker->GetAbilitySystemComponent()->HasMatchingGameplayTag(MMOGameplayTags::Shared_Status_Battle),
		"Attacker should have Status_Battle"))
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker should have Status_Battle");
		return;
	}


	if (!AssertTrue(Defender->GetBattleComponent()->BattleCharacter != nullptr,
	                "After battle Defender should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have BattleCharacter");
		return;
	}

	if (!AssertTrue(Defender->GetBattleComponent()->WorldCharacter != nullptr,
	                "After battle Defender should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have WorldCharacter");
		return;
	}

	if (!AssertTrue(Attacker->GetBattleComponent()->BattleCharacter != nullptr,
	                "After battle Attacker should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have BattleCharacter");
		return;
	}

	if (!AssertTrue(Attacker->GetBattleComponent()->WorldCharacter != nullptr,
	                "After battle Attacker should have WorldCharacter"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have linked character");
		return;
	}


	if (!AssertTrue(Defender->GetBattleComponent()->BattleCharacter->GetBattleComponent()->BattleCharacter != nullptr,
	                "After battle Defender should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have linked character");
		return;
	}
	if (!AssertTrue(Defender->GetBattleComponent()->BattleCharacter->GetBattleComponent()->WorldCharacter != nullptr,
	                "After battle Defender should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have linked character");
		return;
	}

	if (!AssertTrue(Attacker->GetBattleComponent()->BattleCharacter->GetBattleComponent()->BattleCharacter != nullptr,
	                "After battle Defender should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have linked character");
		return;
	}
	if (!AssertTrue(Attacker->GetBattleComponent()->BattleCharacter->GetBattleComponent()->WorldCharacter != nullptr,
	                "After battle Defender should have linked character"))
	{
		FinishTest(EFunctionalTestResult::Error, "After battle Defender should have linked character");
		return;
	}

	if (!AssertTrue(
		Defender->GetBattleComponent()->BattleCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(
			MMOGameplayTags::Shared_Status_Battle),
		"linked character should have Status_Battle tag"))
	{
		FinishTest(EFunctionalTestResult::Error, "linked character should have Status_Battle tag");
		return;
	}

	if (!AssertTrue(
		Attacker->GetBattleComponent()->BattleCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(
			MMOGameplayTags::Shared_Status_Battle),
		"linked character should have Status_Battle tag"))
	{
		FinishTest(EFunctionalTestResult::Error, "BattleCharacter should have Status_Battle tag");
		return;
	}

	if (!AssertTrue(
		Attacker->GetBattleComponent()->BattleCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(
			MMOGameplayTags::Shared_Status_Battle),
		"linked character should have Status_Battle tag"))
	{
		FinishTest(EFunctionalTestResult::Error, "BattleCharacter should have Status_Battle tag");
		return;
	}

	if (!AssertTrue(Attacker->GetBattleComponent()->BattleCharacter->GetBattleComponent()->WorldCharacter == Attacker,
	                "WorldCharacter should be Attacker"))
	{
		FinishTest(EFunctionalTestResult::Error, "WorldCharacter should be Attacker");
		return;
	}
	if (!AssertTrue(Defender->GetBattleComponent()->BattleCharacter->GetBattleComponent()->WorldCharacter == Defender,
	                "WorldCharacter should be Defender"))
	{
		FinishTest(EFunctionalTestResult::Error, "WorldCharacter should be Defender");
		return;
	}


	FinishTest(EFunctionalTestResult::Succeeded, "Test succeeded");
}

void AStartBattleTest::PrepareTest()
{
	Super::PrepareTest();


	if (!Defender)
	{
		FinishTest(EFunctionalTestResult::Error, "Defender not setuped");
	}

	if (!Attacker)
	{
		FinishTest(EFunctionalTestResult::Error, "Attacker not setuped");
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

	Debug::Print("ABattleFunctionalTest::PrepareTest", this);
}
