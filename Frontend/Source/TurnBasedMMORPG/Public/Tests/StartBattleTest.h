// 

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "StartBattleTest.generated.h"


class AMMOPlayerState;
class AMMORPGCharacter;

UCLASS()
class TURNBASEDMMORPG_API AStartBattleTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStartBattleTest();

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<AMMOPlayerState> PlayerStateToSpawn;

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Attacker;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Defender;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartTest() override;
	virtual void PrepareTest() override;
};
