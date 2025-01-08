// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "AI/Navigation/NavigationInvokerInterface.h"
#include "BattleSystem/BattleComponentInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "MMORPGCharacter.generated.h"

class UNavigationInvokerComponent;
class UWidgetComponent;
class UAbilityStartupDataAsset;
class UBaseAttributeSet;

UCLASS(Blueprintable, Abstract)
class TURNBASEDMMORPG_API AMMORPGCharacter : public ACharacter, public IAbilitySystemInterface, public IInteractable,
                                             public IBattleComponentInterface, public IGenericTeamAgentInterface,
                                             public INavigationInvokerInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UAbilityStartupDataAsset> BaseStartupData = {};

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNavigationInvokerComponent> NavigationInvoker;

protected:
	UPROPERTY(VisibleAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWidgetComponent> AboveHeadWidget;

public:
	AMMORPGCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override PURE_VIRTUAL(, return {};);

	virtual void PossessedBy(AController* NewController) override;

	virtual EInteractType GetInteractionType() override;

	virtual AActor* GetActor() override { return this; }

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	virtual UBattleComponent* GetBattleComponent() const override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	virtual FVector GetNavigationInvokerLocation() const override;
};
