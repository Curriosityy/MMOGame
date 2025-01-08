#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "EndTurnAbilityTest.generated.h"

class ABattleManager;
class UBattle;
class UMMOBaseGameplayAbility;
class AMMOPlayerState;
class AMMORPGCharacter;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API AEndTurnAbilityTest : public AFunctionalTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<AMMOPlayerState> PlayerStateToSpawn;

	UPROPERTY(EditAnywhere, Category = "BattleFunctionalTest")
	TSubclassOf<UMMOBaseGameplayAbility> EndTurnAbility;

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
};
