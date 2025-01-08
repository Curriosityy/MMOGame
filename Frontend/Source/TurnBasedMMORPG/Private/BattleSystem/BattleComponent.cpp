#include "BattleSystem/BattleComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "DebugHelper.h"
#include "GenericTeamAgentInterface.h"
#include "Tags.h"
#include "TimerManager.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "Algo/Accumulate.h"
#include "BattleSystem/Battle.h"
#include "BattleSystem/BattleManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UBattleComponent::UBattleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UBattleComponent::BeginPlay()
{
	Super::BeginPlay();


	// ...
}

APawn* UBattleComponent::GetPawn() const
{
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		return Pawn;
	}

	return Cast<APlayerState>(GetOwner())->GetPawn();
}

void UBattleComponent::SetTarget(UBattleComponent* Target)
{
	check(Target)

	if (Cast<IGenericTeamAgentInterface>(Target->GetOwner())->GetTeamAttitudeTowards(*GetOwner()) ==
		ETeamAttitude::Friendly)
	{
		FriendlyTarget = Target;
		return;
	}

	EnemyTarget = Target;
}

// Called every frame
void UBattleComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UBattleComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, EnemyTarget, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, FriendlyTarget, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StartLocation, COND_None, REPNOTIFY_Always);
}

void UBattleComponent::AddToQueue(UMMOBattleAbility* Ability)
{
	AttackQueue.Add({Ability});
	OnQueueUpdated.Broadcast(AttackQueue);
}

void UBattleComponent::RemoveFromQueue(int index)
{
	AttackQueue.RemoveAt(index);
	OnQueueUpdated.Broadcast(AttackQueue);
}

void UBattleComponent::ClearQueue()
{
	AttackQueue.Empty();
	OnQueueUpdated.Broadcast(AttackQueue);
}


void UBattleComponent::EndTurn()
{
	bool bIsSelectTurn = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent()->HasMatchingGameplayTag(
		MMOGameplayTags::Shared_Status_CurrentTurn);

	if (!bIsSelectTurn)
	{
		return;
	}

	if (TimerHandler.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
	}

	Debug::Print("UBattleComponent::EndTurn", this);
	//Dropped when server call (AI)
	SendTurnEnded(AttackQueue);

	if (!GetOwner()->HasAuthority())
	{
	}


	// ensureMsgf(!SendTurnEnded_Validate(AttackQueue), TEXT("SendTurnEnded_Validate AI VALUES ARE INVALID"));
	//
	// 	SendTurnEnded_Implementation(AttackQueue);
}

const TArray<FAttackStruct>& UBattleComponent::GetQueue()
{
	return AttackQueue;
}


bool UBattleComponent::SendTurnEnded_Validate(const TArray<FAttackStruct>& TurnQueue)
{
	auto currentAP = Cast<UBaseAttributeSet>(Cast<IAbilitySystemInterface>(GetOwner())->
	                                         GetAbilitySystemComponent()->
	                                         GetAttributeSet(UBaseAttributeSet::StaticClass()))->
		GetCurrentAbilityPoints();

	bool bIsSelectTurn = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent()->HasMatchingGameplayTag(
		MMOGameplayTags::Shared_Status_CurrentTurn);

	int APReq = 0;
	for (const FAttackStruct& Queue : TurnQueue)
	{
		APReq += Queue.BattleAbility->GetActionPointsRequired();
	}

	return currentAP - APReq >= 0 && bIsSelectTurn;
}

void UBattleComponent::SendTurnEnded_Implementation(const TArray<FAttackStruct>& TurnQueue)
{
	if (GetOwner()->HasAuthority())
	{
		AttackQueue = TurnQueue;
		OnTurnEnd.Broadcast(this);
		Debug::Print("UBattleComponent::SendTurnEnded_Implementation", this);
	}
}

void UBattleComponent::StartRound_Implementation()
{
	Debug::Print("UBattleComponent::StartRound_Implementation", this);
	FTimerDelegate dele = FTimerDelegate::CreateUObject(this, &ThisClass::EndTurn);
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, dele, UBattle::GetTurnTime(), false);
}
