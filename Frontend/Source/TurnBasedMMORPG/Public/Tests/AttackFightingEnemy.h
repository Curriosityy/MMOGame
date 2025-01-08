#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "AttackFightingEnemy.generated.h"

class AMMOPlayerState;
class AMMORPGCharacter;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API AAttackFightingEnemy : public AFunctionalTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Attacker;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Attacker2;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Defender;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<AMMOPlayerState> PlayerStateToSpawn;

public:
	virtual void PrepareTest() override;
	virtual void StartTest() override;
	virtual void Tick(float DeltaSeconds) override;
};
