// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MultiplayerNetworkConnectionSubsystem.h"

#include "HttpModule.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Misc/ConfigCacheIni.h"


FString UMultiplayerNetworkConnectionSubsystem::GetAPICustomerKey() const
{
	return APICustomerKey;
}

FString UMultiplayerNetworkConnectionSubsystem::GetAPIPath() const
{
	return APIPath;
}


FString UMultiplayerNetworkConnectionSubsystem::GetInstanceManagementAPIPath() const
{
	return InstanceManagementAPIPath;
}


FString UMultiplayerNetworkConnectionSubsystem::GetCharacterPersistenceAPIPath() const
{
	return CharacterPersistenceAPIPath;
}


void UMultiplayerNetworkConnectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// ...
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("OWSAPICustomerKey"),
		APICustomerKey,
		GGameIni
	);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("OWS2APIPath"),
		APIPath,
		GGameIni
	);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("OWS2InstanceManagementAPIPath"),
		InstanceManagementAPIPath,
		GGameIni
	);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("OWS2CharacterPersistenceAPIPath"),
		CharacterPersistenceAPIPath,
		GGameIni
	);
}
