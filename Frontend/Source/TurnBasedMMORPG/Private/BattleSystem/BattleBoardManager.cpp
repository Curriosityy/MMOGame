#include "BattleSystem/BattleBoardManager.h"

#include "DebugHelper.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BattleSystem/BattleBoard.h"
#include "BattleSystem/BattleNavMeshPool.h"
#include "Builders/CubeBuilder.h"
#include "Components/BrushComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "NavMesh/NavMeshBoundsVolume.h"

// Sets default values
ABattleBoardManager::ABattleBoardManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABattleBoardManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ABattleBoard::StaticClass(), Actors);

	for (AActor* NavMesh : Actors)
	{
		BattleBoardPool.Enqueue(Cast<ABattleBoard>(NavMesh));
	}
}

// Called every frame
void ABattleBoardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABattleBoard* ABattleBoardManager::GetBoardFromPool()
{
	ABattleBoard* board{};
	BattleBoardPool.Dequeue(board);
	return board;
}

void ABattleBoardManager::AddBoardToPool(ABattleBoard* Board)
{
	BattleBoardPool.Enqueue(Board);
}

ABattleBoard* ABattleBoardManager::PeekBoardFromPool()
{
	ABattleBoard* board{};
	BattleBoardPool.Peek(board);
	return board;
}
