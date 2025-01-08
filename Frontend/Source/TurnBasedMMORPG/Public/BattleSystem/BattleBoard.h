#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleBoard.generated.h"

UENUM()
enum ETeam
{
	Team1,
	Team2,
};

UCLASS(Abstract)
class TURNBASEDMMORPG_API ABattleBoard : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> RootComp;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<USceneComponent>> Team1;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<USceneComponent>> Team2;

public:
	// Sets default values for this actor's properties
	ABattleBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	const FTransform& GetSpawnPlace(ETeam Team, int PlaceId);
};
