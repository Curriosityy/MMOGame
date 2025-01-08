#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GenericTeamAgentInterface.h"
#include "BattleSystem/BattleComponentInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Interactable.h"
#include "Subsystems/NetCharactersControllerService.h"
#include "MMOPlayerState.generated.h"

class UAbilityDataAsset;
class UAbilityStartupDataAsset;
class UPlayerAttributeSet;
class UMMOPlayerAbilitySystemComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameChanged, const FString&, NewPlayerName);

UCLASS()
class TURNBASEDMMORPG_API AMMOPlayerState : public APlayerState, public IAbilitySystemInterface,
                                            public IBattleComponentInterface, public IGenericTeamAgentInterface,
                                            public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMMOPlayerAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerAttributeSet> AttributeSet;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBattleComponent> BattleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySystem", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UAbilityStartupDataAsset> PlayerSpecificData = {};

	//TODO:LOAD FROM DB
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAbilityDataAsset> BattleAbilityBinding{};

public:
	AMMOPlayerState();
	void TryBindNewAbility(FGameplayAbilitySpec* SpecToCheck) const;
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UBattleComponent* GetBattleComponent() const override;
	void Setup(const FFullCharInfo& FullCharInfo);

	virtual void HandleWelcomeMessage() override;
	virtual void OnRep_PlayerName() override;

	FOnNameChanged OnPlayerNameChanged;

	virtual FString GetHumanReadableName() const override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	virtual EInteractType GetInteractionType() override;
	virtual AActor* GetActor() override;
};
