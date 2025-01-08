#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "GameFramework/Actor.h"
#include "BattleBoardManager.generated.h"

class ABattleNavMeshPool;
class ABattleBoard;

UCLASS()
class TURNBASEDMMORPG_API ABattleBoardManager : public AActor
{
	GENERATED_BODY()


	TQueue<ABattleBoard*> BattleBoardPool;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	TArray<TSubclassOf<ABattleBoard>> PossibleBoardToGenerate;

public:
	// Sets default values for this actor's properties
	ABattleBoardManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ABattleBoard* GetBoardFromPool();
	void AddBoardToPool(ABattleBoard* Board);
	ABattleBoard* PeekBoardFromPool();
};
