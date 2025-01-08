// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "MainMenuWidget.generated.h"

class FOnButtonClickedEvent;
class UButton;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API UMainMenuWidget : public UMMOBaseWidget
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> LoginButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> RegisterButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> OptionsButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> ExitButton;

public:
	UFUNCTION()
	void OnExitClick();
	UFUNCTION()
	void OnPlayClicked();
	virtual void NativeConstruct() override;

	FOnButtonClickedEvent& GetOptionsButtonClickedEvent() const;
	FOnButtonClickedEvent& GetLoginButtonClickedEvent() const;
	FOnButtonClickedEvent& GetRegisterButtonClickedEvent() const;
};
