#include "BattleSystem/BattleManager.h"

#include "BattleSystem/Battle.h"
#include "BattleSystem/BattleBoard.h"
#include "BattleSystem/BattleComponent.h"
#include "Controllers/PlayerBattleController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleManager::ABattleManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABattleManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABattleManager::AddBattle(UBattle* Battle)
{
	Battles.Add(Battle);
}

UBattle* ABattleManager::FindBattle(APawn* PawnToFind)
{
	for (UBattle* Battle : Battles)
	{
		if (Battle->GetPlayers().ContainsByPredicate([&](const UBattleComponent* Fighter)
		{
			return Fighter->BattleCharacter == PawnToFind || Fighter->WorldCharacter == PawnToFind;
		}))
		{
			return Battle;
		}
	}

	return nullptr;
}
