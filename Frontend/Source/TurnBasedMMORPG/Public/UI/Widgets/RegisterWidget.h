// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "RegisterWidget.generated.h"

class FOnButtonClickedEvent;
class UButton;
class UEditableText;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API URegisterWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UEditableText> PasswordText;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UEditableText> EmailText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> RegisterButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> BackButton;

	UFUNCTION()
	void TryRegister();

public:
	virtual void NativeConstruct() override;
	FOnButtonClickedEvent& GetRegisterButtonClickedEvent() const;
	FOnButtonClickedEvent& GetBackButtonClickedEvent() const;
};
