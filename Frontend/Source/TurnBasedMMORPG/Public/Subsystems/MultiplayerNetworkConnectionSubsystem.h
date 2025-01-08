// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerNetworkConnectionSubsystem.generated.h"

/**
 * 
 */
UENUM()
enum EApiType
{
	None,
	PublicApi,
	InstanceManagementAPI,
	CharacterPersistenceAPI,
};

UCLASS(Abstract)
class TURNBASEDMMORPG_API UMultiplayerNetworkConnectionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	//Connection keys
	FString APICustomerKey;
	FString APIPath;
	FString InstanceManagementAPIPath;
	FString CharacterPersistenceAPIPath;

protected:
	FString GetAPICustomerKey() const;
	FString GetAPIPath() const;
	FString GetInstanceManagementAPIPath() const;
	FString GetCharacterPersistenceAPIPath() const;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
