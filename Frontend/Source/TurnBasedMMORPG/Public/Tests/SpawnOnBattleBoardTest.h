#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "SpawnOnBattleBoardTest.generated.h"

class ABattleBoardManager;
class ABattleManager;
class ABattleBoard;
class AMMORPGCharacter;
class AMMOPlayerState;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API ASpawnOnBattleBoardTest : public AFunctionalTest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<AMMOPlayerState> PlayerStateToSpawn;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Attacker;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Defender;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<ABattleBoardManager> BattleBoardManager;

	UPROPERTY(Transient)
	TObjectPtr<ABattleBoard> BattleBoard;

public:
	virtual void PrepareTest() override;
	virtual void StartTest() override;
	virtual void Tick(float DeltaSeconds) override;
};
