#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "BattleComponent.generated.h"

class AMMORPGCharacter;
class UMMOBattleAbility;
class UBattle;

USTRUCT(Blueprintable)
struct FAttackStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMMOBattleAbility> BattleAbility;
};

class UBaseAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnEnd, UBattleComponent*, Sender);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueueUpdated, const TArray<FAttackStruct>&)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TURNBASEDMMORPG_API UBattleComponent : public UActorComponent
{
	friend UBattle;

	GENERATED_BODY()


	UPROPERTY(Replicated, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBattleComponent> FriendlyTarget{};
	UPROPERTY(Replicated, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBattleComponent> EnemyTarget{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TArray<FAttackStruct> AttackQueue{};

	FTimerHandle TimerHandler;

	const float TurnSpeed = 12;

public:
	//Not replicated character, valid on server only
	UPROPERTY(BlueprintReadOnly, Transient, meta=(AllowPrivateAccess=true))
	TObjectPtr<AMMORPGCharacter> WorldCharacter;
	UPROPERTY(BlueprintReadOnly, Transient, meta=(AllowPrivateAccess=true))
	TObjectPtr<AMMORPGCharacter> BattleCharacter;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FTransform StartLocation;
	// Sets default values for this component's properties
	UBattleComponent();

	FOnTurnEnd OnTurnEnd;
	FOnQueueUpdated OnQueueUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	APawn* GetPawn() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetTarget(UBattleComponent* Target);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AddToQueue(UMMOBattleAbility* Ability);

	UFUNCTION(BlueprintCallable)
	void RemoveFromQueue(int index);

	UFUNCTION(BlueprintCallable)
	void ClearQueue();

	UFUNCTION(BlueprintCallable)
	void EndTurn();

	UFUNCTION(Client, Reliable)
	void StartRound();

	UFUNCTION(Server, Reliable, WithValidation)
	void SendTurnEnded(const TArray<FAttackStruct>& TurnQueue);
	const TArray<FAttackStruct>& GetQueue();
};
