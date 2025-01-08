// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/MainMenuWidget.h"

#include "Components/Button.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/MultiplayerNetworkConnectionSubsystem.h"


void UMainMenuWidget::OnExitClick()
{
	UKismetSystemLibrary::QuitGame(this,
	                               {},
	                               EQuitPreference::Type::Quit,
	                               true);
}

void UMainMenuWidget::OnPlayClicked()
{
	//UGameInstance::GetSubsystem<UMultiplayerSessionsSubsystem>()->JoinServer();
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FOnButtonClickedEvent& UMainMenuWidget::GetLoginButtonClickedEvent() const
{
	return LoginButton->OnClicked;
}

FOnButtonClickedEvent& UMainMenuWidget::GetRegisterButtonClickedEvent() const
{
	return RegisterButton->OnClicked;
}

FOnButtonClickedEvent& UMainMenuWidget::GetOptionsButtonClickedEvent() const
{
	return OptionsButton->OnClicked;
}
