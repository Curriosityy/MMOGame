// Copyright 2023 Sabre Dart Studios


#include "UI/Widgets/LoginUserWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"

void ULoginUserWidget::TryToLogin()
{
	GetGameInstance()->GetSubsystem<UNetAccountService>()->LoginAndCreateSession(
		LoginText->GetText().ToString(), PasswordText->GetText().ToString());
}

FOnButtonClickedEvent& ULoginUserWidget::GetLoginButtonClickedEvent() const
{
	return LoginButton->OnClicked;
}

FOnButtonClickedEvent& ULoginUserWidget::GetBackButtonClickedEvent() const
{
	return BackButton->OnClicked;
}

void ULoginUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoginButton)
	{
		LoginButton->OnClicked.AddUniqueDynamic(this, &ThisClass::TryToLogin);
	}
}
