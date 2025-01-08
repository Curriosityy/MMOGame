#pragma once

#include "CoreMinimal.h"
#include "Character/MMORPGCharacter.h"
#include "UObject/NoExportTypes.h"
#include "Battle.generated.h"

class ABattleBoard;
class UBattleComponent;
/**
 * 
 */


UCLASS()
class TURNBASEDMMORPG_API UBattle : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UBattleComponent* CurrentTurnComponent;
	int currentTurnIndex;

	UPROPERTY()
	TArray<UBattleComponent*> Team1Players;
	UPROPERTY()
	TArray<UBattleComponent*> Team2Players;

	TArray<UBattleComponent*> BattleQueue;

	//TODO:Initiative based on stat (str give more initiative in melee trun etc.)
	UPROPERTY()
	ABattleBoard* BattleBoard;
	static int CalculateInitiative(const UAbilitySystemComponent* ASC);
	void RollBattleQueue();

public:
	void StartNewTurn();
	AMMORPGCharacter* GetCurrentTurnOwner();

	FORCEINLINE static float GetTurnTime() { return 12; }

	UFUNCTION()
	void OnTurnEnd(UBattleComponent* Sender);

	static void SetupIfPlayer(const UBattleComponent* BattleComponent);
	static AMMORPGCharacter* GetPawn(const UBattleComponent* BattleComponent);


	void StartBattle(ABattleBoard* BBoard, const TArray<UBattleComponent*>& Attackers,
	                 const TArray<UBattleComponent*>& Defenders);

	void SimulateBattle();
	void EndSimualtionBattle();

	virtual void BeginDestroy() override;

	TArray<UBattleComponent*> GetPlayers() const;
};
