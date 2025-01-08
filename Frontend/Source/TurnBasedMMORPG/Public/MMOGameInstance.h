// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OWSGameInstance.h"
#include "Engine/GameInstance.h"
#include "MMOGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOGameInstance : public UGameInstance
{
	GENERATED_BODY()

	FString SessionGUID = "";

public:
	UFUNCTION()
	void OnLoginSuccess(const FString& UsserSessionGUID);

	FORCEINLINE FString GetUserSessionGUID() { return SessionGUID; }

	bool IsSessionValid();
	virtual void OnStart() override;
};
