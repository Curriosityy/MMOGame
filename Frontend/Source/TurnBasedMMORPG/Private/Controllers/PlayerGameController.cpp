// Copyright Epic Games, Inc. All Rights Reserved.

#include "Controllers/PlayerGameController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DebugHelper.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "MMOInputComponent.h"
#include "MMOPlayerState.h"
#include "NavigationSystem.h"
#include "Tags.h"
#include "AbilitySystem/MMOAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBaseGameplayAbility.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "AI/NavigationSystemBase.h"
#include "DataAsset/AbilityDataAsset.h"
#include "DataAsset/InputDataAsset.h"
#include "DTOs/TryAddAbilityDTO.h"
#include "Engine/LocalPlayer.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameModes/InGameGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavMesh/RecastNavMesh.h"
#include "Net/UnrealNetwork.h"
#include "Subsystems/NetCharactersControllerService.h"
#include "UI/InGameHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APlayerGameController::APlayerGameController()
{
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	PathFollowComp = CreateDefaultSubobject<UPathFollowingComponent>("PathFollowingComp");
}

void APlayerGameController::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
}

void APlayerGameController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	Debug::Print("APlayerGameController::SetupInputComponent", this);
	// Set up action bindings
	if (UMMOInputComponent* EIC = Cast<UMMOInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EIC->BindNativeInputAction(InputData,
		                           MMOGameplayTags::InputTag_SetDestination_Click,
		                           ETriggerEvent::Started,
		                           this,
		                           &APlayerGameController::OnInputStarted);

		EIC->BindNativeInputAction(InputData,
		                           MMOGameplayTags::InputTag_SetDestination_Click,
		                           ETriggerEvent::Triggered,
		                           this,
		                           &APlayerGameController::OnSetDestinationTriggered);

		EIC->BindNativeInputAction(InputData,
		                           MMOGameplayTags::InputTag_SetDestination_Click,
		                           ETriggerEvent::Completed,
		                           this,
		                           &APlayerGameController::OnSetDestinationReleased);

		EIC->BindNativeInputAction(InputData,
		                           MMOGameplayTags::InputTag_SetDestination_Click,
		                           ETriggerEvent::Canceled,
		                           this,
		                           &APlayerGameController::OnSetDestinationReleased);

		EIC->BindAbilityInputAction(InputData, this, &ThisClass::OnAbilityPressed, &ThisClass::OnAbilityReleased);
		EIC->BindAbilityInputAction(BattleInputData, this, &ThisClass::OnAbilityPressed, &ThisClass::OnAbilityReleased);

		return;
	}

	UE_LOG(LogTemplateCharacter, Error,
	       TEXT(
		       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
	       ), *GetNameSafe(this));
}

void APlayerGameController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void APlayerGameController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}


void APlayerGameController::Interact_Implementation(const EInteractType InteractionType, AActor* Interactable)
{
	check(Cast<IInteractable>(Interactable));

	Cast<IInteractable>(Interactable)->Interact(InteractionType, GetPawn<AMMORPGCharacter>());
}


void APlayerGameController::ManageShortPress()
{
	OnAbilityPressed(MMOGameplayTags::InputTag_Interaction);

	//TODO: MOVE EVERYTHING TO ABILITY

	// UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator,
	//                                                FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

	//Move to Ability?
	// StopMovement();
	// Client_GoTo();
	//OnAbilityPressed(MMOGameplayTags::InputTag_Interaction_MoveToClicked);
}

void APlayerGameController::Client_GoTo()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	const FVector AgentNavLocation = GetNavAgentLocation();
	const ANavigationData* NavData = NavSys->GetNavDataForProps(GetNavAgentPropertiesRef(), AgentNavLocation);
	const bool bAlreadyAtGoal = PathFollowComp->HasReached(CachedDestination, EPathFollowingReachMode::OverlapAgent);

	if (bAlreadyAtGoal)
	{
		return;
	}

	// script source, keep only one move request at time
	if (PathFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PathFollowComp->AbortMove(
			*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
			, FAIRequestID::AnyRequest,
			bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
	}

	// script source, keep only one move request at time
	if (PathFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PathFollowComp->AbortMove(
			*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);
	}


	FPathFindingQuery Query(this, *NavData, AgentNavLocation, CachedDestination);
	FPathFindingResult Result = NavSys->FindPathSync(Query);
	PathFollowComp->RequestMove(FAIMoveRequest(CachedDestination), Result.Path);
	Server_MoveToLocation(CachedDestination, AgentNavLocation);
}

void APlayerGameController::Server_MoveToLocation_Implementation(const FVector& GoalLocation,
                                                                 const FVector& StartPathFind)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	const ANavigationData* NavData = NavSys->GetNavDataForProps(GetNavAgentPropertiesRef(), StartPathFind);

	const bool bAlreadyAtGoal = PathFollowComp->HasReached(GoalLocation, EPathFollowingReachMode::OverlapAgent);

	// script source, keep only one move request at time
	if (PathFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PathFollowComp->AbortMove(
			*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
			, FAIRequestID::AnyRequest,
			bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
	}

	// script source, keep only one move request at time
	if (PathFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PathFollowComp->AbortMove(
			*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);
	}

	FPathFindingQuery Query(this, *NavData, StartPathFind, GoalLocation);
	FPathFindingResult Result = NavSys->FindPathSync(Query);
	PathFollowComp->RequestMove(FAIMoveRequest(GoalLocation), Result.Path);
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Vector);
}

void APlayerGameController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		ManageShortPress();
	}

	FollowTime = 0.f;
}

void APlayerGameController::SetupHUD()
{
	if (PlayerState && GetHUD<AInGameHUD>())
	{
		GetHUD<AInGameHUD>()->SetPlayerState(GetPlayerState<AMMOPlayerState>());
	}
}

void APlayerGameController::InitPlayerState()
{
	Super::InitPlayerState();
}


void APlayerGameController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void APlayerGameController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);

	PathFollowComp->SetMovementComponent(P->GetMovementComponent());
}

void APlayerGameController::SetupPositionData(const FFullCharInfo& CharacterFullInfoDto)
{
	StartLocation = {
		CharacterFullInfoDto.CharacterData.X, CharacterFullInfoDto.CharacterData.Y, CharacterFullInfoDto.CharacterData.Z
	};
	StartRotation = {0, CharacterFullInfoDto.CharacterData.RY, 0};
	Info = CharacterFullInfoDto;
	Debug::Print(FString::Printf(
		             TEXT("Registered spawning ponint as Location : %s, Rotation : %s"),
		             *StartLocation.ToString(),
		             *StartRotation.ToString()), this);

	GetPlayerState<AMMOPlayerState>()->Setup(CharacterFullInfoDto);
	DefaultPawnClass = {FSoftObjectPath(CharacterFullInfoDto.CharacterData.DefaultPawnClassPath)};
}

void APlayerGameController::OnAbilityPressed(FGameplayTag GameplayTag)
{
	if (GetPawn())
	{
		UMMOAbilityBlueprintLibrary::GetMMOAbilityComponentSystem(GetPawn())->OnAbilityInputPressed(GameplayTag);
	}
}

void APlayerGameController::OnAbilityReleased(FGameplayTag GameplayTag)
{
	if (GetPawn())
	{
		UMMOAbilityBlueprintLibrary::GetMMOAbilityComponentSystem(GetPawn())->OnAbilityInputReleased(GameplayTag);
	}
}

void APlayerGameController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		return;
	}

	SetupHUD();
}

void APlayerGameController::SpawnPawn_Implementation()
{
	GetWorld()->GetAuthGameMode<AInGameGameMode>()->SpawnSoftPawnAndPossess(
		{StartRotation, StartLocation}, DefaultPawnClass, this);
}

bool APlayerGameController::SpawnPawn_Validate()
{
	return true;
}

void APlayerGameController::LoadScreen_Implementation(const bool Show)
{
	GetHUD<AInGameHUD>()->ShowLoadScreen(Show);
}

void APlayerGameController::SetupBattleHUD_Implementation(const bool Show)
{
	//GetHUD<AInGameHUD>()->SetupInGameHUD(!Show);
	GetHUD<AInGameHUD>()->SetupBattleHUD(Show);
}


void APlayerGameController::SendLoadedOnClient_Implementation(const UObject* OnLoaded)
{
	ItemLoaded.Broadcast(OnLoaded);
}


void APlayerGameController::SetupBattleInput_Implementation(bool Remove)
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());

	if (!Subsystem)
	{
		return;
	}

	if (Remove)
	{
		Subsystem->RemoveMappingContext(BattleInputData->DefaultMappingContext);
		return;
	}

	Subsystem->AddMappingContext(BattleInputData->DefaultMappingContext, 1);
}
