#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "BattleTurnTest.generated.h"

class UBattle;
class ABattleManager;
class AMMORPGCharacter;
class AMMOPlayerState;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API ABattleTurnTest : public AFunctionalTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<AMMOPlayerState> PlayerStateToSpawn;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Attacker;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Defender;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<ABattleManager> BattleManager;

	TWeakObjectPtr<UBattle> Battle;

	TWeakObjectPtr<AMMORPGCharacter> StartTurnOwner;

public:
	virtual void PrepareTest() override;
	virtual void StartTest() override;
	virtual void Tick(float DeltaSeconds) override;
};
