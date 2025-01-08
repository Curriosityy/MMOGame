#include "BattleSystem/BattleNavMeshPool.h"

#include "NetworkingFunctionLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NavMesh/NavMeshBoundsVolume.h"

// Sets default values
ABattleNavMeshPool::ABattleNavMeshPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABattleNavMeshPool::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ANavMeshBoundsVolume::StaticClass(), Actors);
	for (AActor* NavMesh : Actors)
	{
		if (NavMesh->GetActorLabel().Contains("Pool"))
		{
			NavMeshQueue.Enqueue(Cast<ANavMeshBoundsVolume>(NavMesh));
		}
	}
}

ANavMeshBoundsVolume* ABattleNavMeshPool::GetNavMeshFromPool()
{
	ANavMeshBoundsVolume* NavmeshToReturn{};
	NavMeshQueue.Dequeue(NavmeshToReturn);

	return NavmeshToReturn;
}

void ABattleNavMeshPool::AddNavmeshToPool(ANavMeshBoundsVolume* NavMeshToAdd)
{
	NavMeshQueue.Enqueue(NavMeshToAdd);
}
