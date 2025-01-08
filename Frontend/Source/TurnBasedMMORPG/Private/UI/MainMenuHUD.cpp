#include "UI/MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/NamedSlot.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"
#include "UI/Widgets/CharacterSelectionWidget.h"
#include "UI/Widgets/CreateCharacterWidget.h"
#include "UI/Widgets/LoginUserWidget.h"
#include "UI/Widgets/TitleMenuWidget.h"
#include "UI/Widgets/MainMenuWidget.h"
#include "UI/Widgets/RegisterWidget.h"

void AMainMenuHUD::ShowWidget(UUserWidget* WidgetToShow)
{
	checkf(WidgetToShow, TEXT("WidgetToShow is NULLPTR"));

	if (CurrentVisibielWidget)
	{
		TitleMenuWidget->MenuSlot->RemoveChild(CurrentVisibielWidget);
		CurrentVisibielWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	WidgetToShow->SetVisibility(ESlateVisibility::Visible);
	TitleMenuWidget->MenuSlot->AddChild(WidgetToShow);
	CurrentVisibielWidget = WidgetToShow;
}


void AMainMenuHUD::SetLoginScreenMain()
{
	ShowWidget(LoginMenuWidget);
}

void AMainMenuHUD::SetRegisterWindowMain()
{
	ShowWidget(RegisterWidget);
}

void AMainMenuHUD::SetMainMenuMain()
{
	ShowWidget(MainMenuWidget);
}

void AMainMenuHUD::ShowCharacterSelection()
{
	ShowWidget(CharacterSelection);
}

void AMainMenuHUD::OnLoginSuccess(const FString& UsserSessionGUID)
{
	ShowCharacterSelection();
}

void AMainMenuHUD::OnCharacterCreated(const FCharacterBaseInfoDTO& Character)
{
	ShowCharacterSelection();
}


void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	UNetAccountService* NetSubsystem = GetGameInstance()->GetSubsystem<UNetAccountService>();
	NetSubsystem->OnLoginSuccess.AddDynamic(this, &ThisClass::OnLoginSuccess);
	NetSubsystem->OnCharacterCreated.AddDynamic(this, &ThisClass::OnCharacterCreated);
}

void AMainMenuHUD::ShowCreateCharacter()
{
	ShowWidget(CreateCharacter);
}

void AMainMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CharacterSelectionClass.GetDefaultObject())
	{
		CharacterSelection = SpawnWidgetAndAddToViewport<UCharacterSelectionWidget>(
			CharacterSelectionClass, ESlateVisibility::Hidden,
			1);
	}

	if (CreateCharacterClass)
	{
		CreateCharacter = SpawnWidgetAndAddToViewport<UCreateCharacterWidget>(
			CreateCharacterClass, ESlateVisibility::Hidden,
			1);
	}

	if (TitleMenuWidgetClass.GetDefaultObject())
	{
		TitleMenuWidget = SpawnWidgetAndAddToViewport<UTitleMenuWidget>(TitleMenuWidgetClass);
	}

	if (LoginMenuWidgetClass.GetDefaultObject())
	{
		LoginMenuWidget = SpawnWidgetAndAddToViewport<ULoginUserWidget>(LoginMenuWidgetClass, ESlateVisibility::Hidden,
		                                                                1);
	}

	if (RegisterWidgetClass.GetDefaultObject())
	{
		RegisterWidget = SpawnWidgetAndAddToViewport<URegisterWidget>(RegisterWidgetClass, ESlateVisibility::Hidden, 1);
	}

	if (MainMenuWidgetClass.GetDefaultObject())
	{
		MainMenuWidget = SpawnWidgetAndAddToViewport<
			UMainMenuWidget>(MainMenuWidgetClass, ESlateVisibility::Visible, 1);
		ShowWidget(MainMenuWidget);
	}

	if (MainMenuWidget)
	{
		MainMenuWidget->GetLoginButtonClickedEvent().AddDynamic(this, &ThisClass::SetLoginScreenMain);
		MainMenuWidget->GetRegisterButtonClickedEvent().AddDynamic(this, &ThisClass::SetRegisterWindowMain);
	}

	if (RegisterWidget)
	{
		RegisterWidget->GetBackButtonClickedEvent().AddDynamic(this, &ThisClass::SetMainMenuMain);
	}

	if (LoginMenuWidget)
	{
		LoginMenuWidget->GetBackButtonClickedEvent().AddDynamic(this, &ThisClass::SetMainMenuMain);
	}

	if (CreateCharacter)
	{
		CreateCharacter->OnCancelButtonClicked().AddDynamic(this, &ThisClass::ShowCharacterSelection);
	}

	if (CharacterSelection)
	{
		CharacterSelection->OnNewCharacterButtonClicked().AddDynamic(this, &ThisClass::ShowCreateCharacter);
		CharacterSelection->OnLogoutButtonClicked().AddDynamic(this, &ThisClass::SetMainMenuMain);
	}
}
