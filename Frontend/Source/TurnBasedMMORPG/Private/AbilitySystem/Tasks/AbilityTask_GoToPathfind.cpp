// 


#include "AbilitySystem/Tasks/AbilityTask_GoToPathfind.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controllers/PlayerGameController.h"
#include "Navigation/PathFollowingComponent.h"

UAbilityTask_GoToPathfind* UAbilityTask_GoToPathfind::GoToPathfind(UGameplayAbility* OwningAbility,
                                                                   AController* Controller,
                                                                   const FVector& Location)
{
	UAbilityTask_GoToPathfind* MyObj = NewAbilityTask<UAbilityTask_GoToPathfind>(OwningAbility);

	MyObj->TargetLocation = Location;
	MyObj->MoverController = Controller;
	return MyObj;
}

UPathFollowingComponent* UAbilityTask_GoToPathfind::InitNavigationControl(AController* Controller)
{
	AAIController* AsAIController = Cast<AAIController>(Controller);
	UPathFollowingComponent* PathFollowingComp = nullptr;

	if (AsAIController)
	{
		PathFollowingComp = AsAIController->GetPathFollowingComponent();
	}
	else
	{
		PathFollowingComp = Controller->FindComponentByClass<UPathFollowingComponent>();
		if (PathFollowingComp == nullptr)
		{
			PathFollowingComp = NewObject<UPathFollowingComponent>(Controller);
			PathFollowingComp->RegisterComponentWithWorld(Controller->GetWorld());
			PathFollowingComp->Initialize();
		}
	}

	return PathFollowingComp;
}

void UAbilityTask_GoToPathfind::OnMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Flags == FPathFollowingResultFlags::Success)
	{
		OnPathfindingReached.Broadcast();
		return;
	}

	OnPathfindingCanceled.Broadcast();
}

void UAbilityTask_GoToPathfind::Activate()
{
	Super::Activate();

	UNavigationSystemV1* NavSys = MoverController.Get()
		                              ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(MoverController->GetWorld())
		                              : nullptr;
	if (NavSys == nullptr || MoverController.Get() == nullptr || MoverController->GetPawn() == nullptr)
	{
		UE_LOG(LogNavigation, Warning,
		       TEXT(
			       "UNavigationSystemV1::SimpleMoveToActor called for NavSys:%s Controller:%s controlling Pawn:%s (if any of these is None then there's your problem"
		       ),
		       *GetNameSafe(NavSys), *GetNameSafe(MoverController.Get()),
		       MoverController.Get() ? *GetNameSafe(MoverController->GetPawn()) : TEXT("NULL"));
		EndTask();
		OnPathfindingCanceled.Broadcast();
		return;
	}

	PFollowComp = InitNavigationControl(MoverController.Get());

	if (PFollowComp == nullptr || !PFollowComp->IsPathFollowingAllowed())
	{
		EndTask();
		OnPathfindingCanceled.Broadcast();
	}

	const bool bAlreadyAtGoal = PFollowComp->HasReached(TargetLocation, EPathFollowingReachMode::OverlapAgent);

	if (bAlreadyAtGoal)
	{
		EndTask();
		OnPathfindingReached.Broadcast();
		return;
	}

	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
		                       , FAIRequestID::AnyRequest,
		                       bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
	}


	const FVector AgentNavLocation = MoverController->GetNavAgentLocation();
	const ANavigationData* NavData = NavSys->GetNavDataForProps(MoverController->GetNavAgentPropertiesRef(),
	                                                            AgentNavLocation);

	PFollowComp->OnRequestFinished.AddUObject(this, &ThisClass::OnMoveFinished);

	if (!NavData)
	{
		EndTask();
		OnPathfindingReached.Broadcast();
		return;
	}

	FPathFindingQuery Query(MoverController.Get(), *NavData, AgentNavLocation, TargetLocation);
	FPathFindingResult Result = NavSys->FindPathSync(Query);

	if (Result.IsSuccessful())
	{
		PFollowComp->RequestMove(FAIMoveRequest(TargetLocation), Result.Path);
		return;
	}

	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
		return;
	}

	EndTask();
	OnPathfindingReached.Broadcast();
}


void UAbilityTask_GoToPathfind::OnDestroy(bool bInOwnerFinished)
{
	AActor* MyActor = GetAvatarActor();

	if (PFollowComp.Get())
	{
		PFollowComp->OnRequestFinished.RemoveAll(this);
	}

	Super::OnDestroy(bInOwnerFinished);
}
