// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerBase.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Interactable.h"
#include "Subsystems/NetAccountService.h"
#include "NavigationData.h"
#include "Subsystems/NetCharactersControllerService.h"
#include "PlayerGameController.generated.h"

struct FFullCharInfo;
class UPathFollowingComponent;
class UAbilityDataAsset;
struct FGameplayTag;
struct FPathFindingResult;
class UInputDataAsset;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
/** Forward declaration to improve compiling times */

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadItem, const UObject*, LoadedItem);

UCLASS(Abstract)
class TURNBASEDMMORPG_API APlayerGameController : public APlayerControllerBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup, meta=(AllowPrivateAccess))
	float PlayerAttackRange{200};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputDataAsset> BattleInputData{};

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPathFollowingComponent> PathFollowComp;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	TObjectPtr<AActor> ClickedActor;

	FFullCharInfo Info;

	UPROPERTY()
	TSoftClassPtr<APawn> DefaultPawnClass;

public:
	FORCEINLINE TSoftClassPtr<APawn> GetDefaultPawnClass() const
	{
		return DefaultPawnClass;
	}

	APlayerGameController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold{0.2f};

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor{};

	FVector StartLocation;
	FRotator StartRotation;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Interact(const EInteractType InteractionType, AActor* Interactable);


	void Client_GoTo();
	void ManageShortPress();
	void OnSetDestinationReleased();
	void SetupHUD();

	virtual void InitPlayerState() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector CachedDestination{};

	bool bIsTouch{}; // Is it a touch device
	float FollowTime{}; // For how long it has been pressed

	UFUNCTION(Server, Reliable)
	void Server_MoveToLocation(const FVector& GoalLocation, const FVector& StartPathFind);

public:
	FOnLoadItem ItemLoaded;

	virtual void AcknowledgePossession(class APawn* P) override;
	void SetupPositionData(const FFullCharInfo& CharacterFullInfoDto);
	UFUNCTION(Client, Reliable)
	void SetupBattleInput(bool Remove);


	UFUNCTION(Client, Reliable)
	void LoadScreen(bool Show);

	UFUNCTION(Client, Reliable)
	void SetupBattleHUD(bool Show);

	UFUNCTION(Server, Reliable)
	void SendLoadedOnClient(const UObject* OnLoaded);

	void OnAbilityPressed(FGameplayTag GameplayTag);

	void OnAbilityReleased(FGameplayTag GameplayTag);

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void SpawnPawn();
};
