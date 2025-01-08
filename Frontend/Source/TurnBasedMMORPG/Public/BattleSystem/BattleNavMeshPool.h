#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "GameFramework/Actor.h"
#include "BattleNavMeshPool.generated.h"

class ANavMeshBoundsVolume;

UCLASS()
class TURNBASEDMMORPG_API ABattleNavMeshPool : public AActor
{
	GENERATED_BODY()

	TQueue<ANavMeshBoundsVolume*> NavMeshQueue;

public:
	// Sets default values for this actor's properties
	ABattleNavMeshPool();

	ANavMeshBoundsVolume* GetNavMeshFromPool();

	void AddNavmeshToPool(ANavMeshBoundsVolume* NavMeshToAdd);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
