#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleManager.generated.h"

class UBattle;

UCLASS()
class TURNBASEDMMORPG_API ABattleManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UBattle*> Battles;

public:
	// Sets default values for this actor's properties
	ABattleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddBattle(UBattle* Battle);
	UBattle* FindBattle(APawn* PawnToFind);
};
