#pragma once

#include "CoreMinimal.h"
#include "Subsystems/MultiplayerNetworkConnectionSubsystem.h"
#include "NetServerInstanceService.generated.h"

/**
 * 
 */
USTRUCT()
struct FZoneInstanceFullInfoDTO
{
	GENERATED_BODY()
	FZoneInstanceFullInfoDTO() = default;

	FZoneInstanceFullInfoDTO(const FString& InMapName,
	                         const FString& InZoneName,
	                         const FString& InWorldCompContainsFilter,
	                         const FString& InWorldCompListFilter,
	                         const int InMapInstanceID,
	                         const int InStatus,
	                         const int InMaxNumberOfInstances,
	                         const FDateTime& InActiveStartTime,
	                         const BYTE InServerStatus,
	                         const FString& InInternalServerIP)
		: MapName(InMapName),
		  ZoneName(InZoneName),
		  WorldCompContainsFilter(InWorldCompContainsFilter),
		  WorldCompListFilter(InWorldCompListFilter),
		  MapInstanceID(InMapInstanceID),
		  Status(InStatus),
		  MaxNumberOfInstances(InMaxNumberOfInstances),
		  ActiveStartTime(InActiveStartTime),
		  ServerStatus(InServerStatus),
		  InternalServerIP(InInternalServerIP)
	{
	}

	FString MapName;
	FString ZoneName;
	FString WorldCompContainsFilter;
	FString WorldCompListFilter;
	int MapInstanceID;
	int Status;
	int MaxNumberOfInstances;
	FDateTime ActiveStartTime;
	BYTE ServerStatus;
	FString InternalServerIP;
};

USTRUCT()
struct FZoneInstanceDTO
{
	GENERATED_BODY()
	FZoneInstanceDTO() = default;

	FZoneInstanceDTO(const int InZoneInstanceID): ZoneInstanceId(InZoneInstanceID)
	{
	}

	UPROPERTY()
	int ZoneInstanceId;
};

USTRUCT()
struct FPlayerNumbersDTO
{
	GENERATED_BODY()
	FPlayerNumbersDTO() = default;

	FPlayerNumbersDTO(const int InZoneInstanceID, const int InNumberOfConnectedPlayers):
		ZoneInstanceID(InZoneInstanceID),
		NumberOfConnectedPlayers(InNumberOfConnectedPlayers)
	{
	}

	UPROPERTY()
	int ZoneInstanceID;

	UPROPERTY()
	int NumberOfConnectedPlayers;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerNumbersChanged);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZoneInstanceInfoReceived, const FZoneInstanceFullInfoDTO&,
                                            ZoneInstanceFullInfoDto);

UCLASS()
class TURNBASEDMMORPG_API UNetServerInstanceService : public UMultiplayerNetworkConnectionSubsystem
{
	GENERATED_BODY()
	void OnZoneInstanceReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                            bool bConnectedSuccessfully);
	void OnConnectedPlayerNumberReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                                     bool bConnectedSuccessfully);

public:
	void GetZoneInstanceFromZoneInstanceID(int32 ZoneInstanceID);
	void UpdateNumberOfPlayers(int32 ZoneInstanceID, int32 ConnectedPlayersNumber);

	FOnPlayerNumbersChanged OnPlayerNumbersChanged;
	FOnZoneInstanceInfoReceived OnZoneInstanceInfoReceived;
};
