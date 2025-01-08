// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "CharacterSelectionWidget.generated.h"

struct FCharacterBaseInfoDTO;
class UCharacterButtonWidget;
class UVerticalBox;
class FOnButtonClickedEvent;
class UButton;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API UCharacterSelectionWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> PlayButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> LogoutButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> NewCharacterButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UPanelWidget> CharactersPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TSubclassOf<UCharacterButtonWidget> CharacterButtonClass;

	UFUNCTION()
	void OnCharacterCreated(const FCharacterBaseInfoDTO& Character);

public:
	FOnButtonClickedEvent& OnPlayButtonClicked() const;
	FOnButtonClickedEvent& OnLogoutButtonClicked() const;
	FOnButtonClickedEvent& OnNewCharacterButtonClicked() const;

	virtual void PostInitProperties() override;
	UFUNCTION()
	void PopulateCharacters(const TArray<FCharacterBaseInfoDTO>& Characters);
	UFUNCTION()
	void OnLoggedIn(const FString& UsserSessionGUID);


	virtual void NativeOnInitialized() override;
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
