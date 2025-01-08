// 


#include "Tests/ReplicatedFunctionalTest.h"

#include "DebugHelper.h"
#include "Character/PlayerCharacter.h"
#include "Engine/Player.h"
#include "GameFramework/PlayerController.h"
#include "Online/CoreOnline.h"


// Sets default values
AReplicatedFunctionalTest::AReplicatedFunctionalTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AReplicatedFunctionalTest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AReplicatedFunctionalTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AReplicatedFunctionalTest::PrepareTest()
{
	Super::PrepareTest();

	if (!PlayerCharacter1)
	{
		FinishTest(EFunctionalTestResult::Error, "Defender not setuped");
	}

	if (!PlayerCharacter2)
	{
		FinishTest(EFunctionalTestResult::Error, "BattleBoardManager not setuped");
	}

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Preparing Server for Client Connection Test..."));
		FString Error;
		FURL DummyURL;
		DummyURL.Map = TEXT("TestMap");

		// Create a mock player
		UPlayer* NewPlayer1 = NewObject<UPlayer>();

		// Spawn the player controller
		PlayerController1 = GetWorld()->SpawnPlayActor(
			NewPlayer1,
			ROLE_AutonomousProxy, // AutonomousProxy for a client
			DummyURL,
			FUniqueNetIdRepl{}, // No UniqueNetId for testing
			Error,
			0 // First player index
		);

		PlayerController1->Possess(PlayerCharacter1);

		UPlayer* NewPlayer2 = NewObject<UPlayer>();

		// Spawn the player controller
		PlayerController2 = GetWorld()->SpawnPlayActor(
			NewPlayer2,
			ROLE_AutonomousProxy, // AutonomousProxy for a client
			DummyURL,
			FUniqueNetIdRepl{}, // No UniqueNetId for testing
			Error,
			0 // First player index
		);
		PlayerController2->Possess(PlayerCharacter1);

		if (PlayerController1 == nullptr)
		{
			FinishTest(EFunctionalTestResult::Failed, "NewPlayerController is null");
		}

		if (PlayerController2 == nullptr)
		{
			FinishTest(EFunctionalTestResult::Failed, "NewPlayerController is null");
		}
		// Perform server setup
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Client Test Ready!"));
	}
}

void AReplicatedFunctionalTest::StartTest()
{
	Super::StartTest();
	Test_Implementation();

	FinishTest(EFunctionalTestResult::Succeeded, "");
}

void AReplicatedFunctionalTest::Test_Implementation()
{
	Debug::Print("AReplicatedFunctionalTest::Test_Implementation", this);
}
