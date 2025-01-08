// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGameInstance.h"

#include "Subsystems/NetAccountService.h"
#include "UI/Widgets/LoginUserWidget.h"

void UMMOGameInstance::OnLoginSuccess(const FString& UsserSessionGUID)
{
	SessionGUID = UsserSessionGUID;
}

bool UMMOGameInstance::IsSessionValid()
{
	return !SessionGUID.IsEmpty();
}

void UMMOGameInstance::OnStart()
{
	Super::OnStart();
	GetSubsystem<UNetAccountService>()->OnLoginSuccess.AddDynamic(this, &ThisClass::OnLoginSuccess);
}
