// Copyright 2023 Sabre Dart Studios


#include "UI/Widgets/CharacterSelectionWidget.h"

#include "Components/Button.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"
#include "UI/Widgets/CharacterButtonWidget.h"

void UCharacterSelectionWidget::OnCharacterCreated(const FCharacterBaseInfoDTO& Character)
{
	PopulateCharacters({Character});
}

FOnButtonClickedEvent& UCharacterSelectionWidget::OnPlayButtonClicked() const
{
	return PlayButton->OnClicked;
}

FOnButtonClickedEvent& UCharacterSelectionWidget::OnLogoutButtonClicked() const
{
	return LogoutButton->OnClicked;
}

FOnButtonClickedEvent& UCharacterSelectionWidget::OnNewCharacterButtonClicked() const
{
	return NewCharacterButton->OnClicked;
}

void UCharacterSelectionWidget::PostInitProperties()
{
	Super::PostInitProperties();
}

void UCharacterSelectionWidget::PopulateCharacters(const TArray<FCharacterBaseInfoDTO>& Characters)
{
	for (const FCharacterBaseInfoDTO& Character : Characters)
	{
		//TODO: ObjectPooling
		UCharacterButtonWidget* Widget = CreateWidget<UCharacterButtonWidget>(GetWorld(), CharacterButtonClass);
		Widget->AddToViewport(1);
		Widget->SetVisibility(ESlateVisibility::Visible);
		Widget->Setup(Character.CharacterName);
		CharactersPanel->AddChild(Widget);
	}
	//TODO: SHOW THIS SCREEN AFTER POPULATE IF ERROR LOGOUT
}

void UCharacterSelectionWidget::OnLoggedIn(const FString& UsserSessionGUID)
{
	GetGameInstance()->GetSubsystem<UNetAccountService>()->GetAllCharacters(UsserSessionGUID);
}

void UCharacterSelectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UNetAccountService* NetSubsystem = GetGameInstance()->GetSubsystem<UNetAccountService>();

	NetSubsystem->OnLoginSuccess.AddDynamic(this, &ThisClass::OnLoggedIn);
	NetSubsystem->OnCharactersReceivedSuccess.AddDynamic(this, &ThisClass::PopulateCharacters);
	NetSubsystem->OnCharacterCreated.AddDynamic(this, &ThisClass::OnCharacterCreated);
}

void UCharacterSelectionWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
}
