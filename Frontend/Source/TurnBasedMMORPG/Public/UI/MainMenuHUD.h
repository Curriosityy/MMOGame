// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "NetworkMessage.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Subsystems/NetAccountService.h"
#include "MainMenuHUD.generated.h"

class UCreateCharacterWidget;
class UCharacterSelectionWidget;
class URegisterWidget;
class UTitleMenuWidget;
class ULoginUserWidget;
class UUserWidget;
class UMainMenuWidget;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentVisibielWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UTitleMenuWidget> TitleMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTitleMenuWidget> TitleMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<ULoginUserWidget> LoginMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<ULoginUserWidget> LoginMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UMainMenuWidget> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<URegisterWidget> RegisterWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<URegisterWidget> RegisterWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UCharacterSelectionWidget> CharacterSelectionClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCharacterSelectionWidget> CharacterSelection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UCreateCharacterWidget> CreateCharacterClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCreateCharacterWidget> CreateCharacter;

	void ShowWidget(UUserWidget* WidgetToShow);

	template <class WidgetClass>
	WidgetClass* SpawnWidgetAndAddToViewport(TSubclassOf<UUserWidget> WidgetToSpawn,
	                                         ESlateVisibility Visibility = ESlateVisibility::Visible,
	                                         int ViewportLayer = 0);

	UFUNCTION()
	void SetLoginScreenMain();
	UFUNCTION()
	void SetRegisterWindowMain();
	UFUNCTION()
	void SetMainMenuMain();
	UFUNCTION()
	void ShowCharacterSelection();
	UFUNCTION()
	void OnLoginSuccess(const FString& UsserSessionGUID);

public:
	UFUNCTION()
	void OnCharacterCreated(const FCharacterBaseInfoDTO& Character);
	virtual void BeginPlay() override;
	UFUNCTION()
	void ShowCreateCharacter();
	virtual void PostInitializeComponents() override;
};

template <class WidgetClass>
WidgetClass* AMainMenuHUD::SpawnWidgetAndAddToViewport(TSubclassOf<UUserWidget> WidgetToSpawn,
                                                       ESlateVisibility Visibility, int ViewportLayer)
{
	static_assert(TIsDerivedFrom<WidgetClass, UUserWidget>::IsDerived, "WidgetClass must be derived from UUserWidget");
	WidgetClass* Widget = Cast<WidgetClass>(CreateWidget(GetWorld(), WidgetToSpawn));

	if (!Widget)
	{
		return nullptr;
	}

	Widget->AddToViewport(ViewportLayer);
	Widget->SetVisibility(Visibility);

	return Widget;
}
