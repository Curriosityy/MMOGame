#include "Subsystems/NetServerInstanceService.h"

#include "JsonObjectConverter.h"
#include "NetworkingFunctionLibrary.h"

void UNetServerInstanceService::OnZoneInstanceReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                       bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnZoneInstanceReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
	if (!ErrorMsg.IsEmpty())
	{
		//TODO RAISE ERROR
		return;
	}

	OnZoneInstanceInfoReceived.Broadcast(
		*UNetworkingFunctionLibrary::Native_GetStructFromJsonObject<FZoneInstanceFullInfoDTO>(JsonObject));
}

void UNetServerInstanceService::OnConnectedPlayerNumberReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                                bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnConnectedPlayerNumberReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
	if (!ErrorMsg.IsEmpty())
	{
		//TODO RAISE ERROR
		return;
	}

	OnPlayerNumbersChanged.Broadcast();
}

void UNetServerInstanceService::GetZoneInstanceFromZoneInstanceID(const int32 ZoneInstanceID)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(FZoneInstanceDTO{ZoneInstanceID}, PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetInstanceManagementAPIPath(),
			"api/Instance/GetZoneInstance",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnZoneInstanceReceived);
		return;
	}

	Debug::Print(TEXT("Logout Error serializing!"),this);
}

void UNetServerInstanceService::UpdateNumberOfPlayers(const int32 ZoneInstanceID, const int32 ConnectedPlayersNumber)
{
	checkf(ZoneInstanceID > 0, TEXT("UpdateNumberOfPlayers::Invalid ZoneInstanceID"));
	checkf(ConnectedPlayersNumber >= 0, TEXT("UpdateNumberOfPlayers::Invalid ConnectedPlayersNumber"));
	FString PostParameters = "";
	if (FJsonObjectConverter::UStructToJsonObjectString(FPlayerNumbersDTO{ZoneInstanceID, ConnectedPlayersNumber},
	                                                    PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetInstanceManagementAPIPath(),
			"api/Instance/UpdateNumberOfPlayers",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnConnectedPlayerNumberReceived);
	}
}
