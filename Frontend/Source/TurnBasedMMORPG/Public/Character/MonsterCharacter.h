// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MMORPGCharacter.h"
#include "Engine/DataTable.h"
#include "UObject/WeakFieldPtr.h"
#include "MonsterCharacter.generated.h"

class UMonsterAttributeSet;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API AMonsterCharacter : public AMMORPGCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem", meta = (AllowPrivateAccess))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TObjectPtr<UMonsterAttributeSet> AttributeSet = {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Battle", meta=(AllowPrivateAccess))
	TObjectPtr<UBattleComponent> BattleComponent = {};

	UPROPERTY(EditDefaultsOnly, Replicated, ReplicatedUsing=Rep_Name, Category="Setup")
	FString MonsterName{"NameNotSet"};

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	FDataTableRowHandle MonsterDataInfo;

public:
	AMonsterCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual EInteractType GetInteractionType() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UBattleComponent* GetBattleComponent() const override;

	virtual FString GetHumanReadableName() const override;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Rep_Name(const FString& OldName);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
