// Copyright 2023 Sabre Dart Studios


#include "UI/Widgets/CharacterButtonWidget.h"

#include "MMOGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"

void UCharacterButtonWidget::OnCharacterSelected(const FCharacterFullInfoDTO& Character)
{
	const FString& Session = Cast<UMMOGameInstance>(GetGameInstance())->GetUserSessionGUID();
	UNetAccountService* netService = GetGameInstance()->GetSubsystem<UNetAccountService>();
	netService->OnCharacterSelected.RemoveDynamic(this, &ThisClass::OnCharacterSelected);
	netService->GetServerToConnectTo(Session, Character.CharName);
}

void UCharacterButtonWidget::OnClicked()
{
	const FString& Session = Cast<UMMOGameInstance>(GetGameInstance())->GetUserSessionGUID();
	UNetAccountService* netService = GetGameInstance()->GetSubsystem<UNetAccountService>();
	netService->OnCharacterSelected.AddDynamic(this, &ThisClass::OnCharacterSelected);
	netService->SetCharacterSelected(CharName, Session);
}

FOnButtonClickedEvent& UCharacterButtonWidget::SelectButtonClickedEvent() const
{
	return SelectButton->OnClicked;
}

void UCharacterButtonWidget::Setup(const FString& InCharName)
{
	CharacterText->SetText(FText::FromString(InCharName));
	CharName = InCharName;
}

void UCharacterButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClicked);
}

void UCharacterButtonWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
}
