#include "UI/Widgets/RegisterWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"

void URegisterWidget::TryRegister()
{
	GetGameInstance()->GetSubsystem<UNetAccountService>()->Register(EmailText->GetText().ToString(),
	                                                                PasswordText->GetText().ToString());
}

void URegisterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RegisterButton->OnClicked.AddDynamic(this, &ThisClass::TryRegister);
}

FOnButtonClickedEvent& URegisterWidget::GetRegisterButtonClickedEvent() const
{
	return RegisterButton->OnClicked;
}

FOnButtonClickedEvent& URegisterWidget::GetBackButtonClickedEvent() const
{
	return BackButton->OnClicked;
}
