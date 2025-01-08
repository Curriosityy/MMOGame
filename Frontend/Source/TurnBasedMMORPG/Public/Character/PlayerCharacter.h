// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MMORPGCharacter.h"
#include "PlayerCharacter.generated.h"

class UClassSpecificDataAsset;
struct FGameplayAbilitySpec;
class AMMOPlayerState;
class UAbilityDataAsset;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API APlayerCharacter : public AMMORPGCharacter
{
	GENERATED_BODY()

	UPROPERTY()
	AMMOPlayerState* MainPlayerState{};

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TObjectPtr<UClassSpecificDataAsset> ClassSpecificAsset;

	bool IsInitialized = false;

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UBattleComponent* GetBattleComponent() const override;

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;

	virtual void OnRep_PlayerState() override;

	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	void InitAbove();

	virtual void Tick(float DeltaSeconds) override;
};
