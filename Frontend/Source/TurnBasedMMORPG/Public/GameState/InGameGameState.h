#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Interfaces/Interactable.h"
#include "InGameGameState.generated.h"

class ABattleManager;
class UGameplayEffect;
class UBattle;
class ABattleBoardManager;
class AMMORPGCharacter;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API AInGameGameState : public AGameState
{
	GENERATED_BODY()
	UPROPERTY()
	TWeakObjectPtr<ABattleBoardManager> BattleBoardManager;
	UPROPERTY()
	TWeakObjectPtr<ABattleManager> BattleManager;

	UPROPERTY()
	TArray<UBattle*> Battles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> BattleGameplayEffect;

public:
	AInGameGameState();
	virtual void HandleBeginPlay() override;

	bool IsValidBattle(AMMORPGCharacter* Attacker, AMMORPGCharacter* Defender);

	void Attack(AMMORPGCharacter* Attacker, AMMORPGCharacter* Defender);
	UFUNCTION()
	//Can be moved elsewhere need to think where
	void TryInteract(EInteractType Interaction, AActor* InteractWith, AMMORPGCharacter* Interactor);
};
