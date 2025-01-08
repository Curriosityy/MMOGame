#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "BattleOnDIfferentBoardsTest.generated.h"

class ABattleBoardManager;
class AMMORPGCharacter;
class AMMOPlayerState;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API ABattleOnDIfferentBoardsTest : public AFunctionalTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<AMMOPlayerState> PlayerStateToSpawn;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")

	TObjectPtr<AMMORPGCharacter> Attacker1;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Defender1;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Attacker2;
	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<AMMORPGCharacter> Defender2;

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TObjectPtr<ABattleBoardManager> BattleBoardManager;

public:
	virtual void PrepareTest() override;
	virtual void StartTest() override;
};
