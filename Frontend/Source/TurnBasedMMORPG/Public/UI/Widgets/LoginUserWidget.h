// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "LoginUserWidget.generated.h"

class UEditableText;
class FOnButtonClickedEvent;
class UButton;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API ULoginUserWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UEditableText> LoginText;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UEditableText> PasswordText;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> LoginButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> BackButton;

protected:
	UFUNCTION()
	void TryToLogin();

public:
	FOnButtonClickedEvent& GetLoginButtonClickedEvent() const;
	FOnButtonClickedEvent& GetBackButtonClickedEvent() const;


	virtual void NativeConstruct() override;
};
