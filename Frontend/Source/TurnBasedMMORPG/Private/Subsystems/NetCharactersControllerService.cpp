// 


#include "Subsystems/NetCharactersControllerService.h"

#include "JsonObjectConverter.h"
#include "NetworkingFunctionLibrary.h"

void UNetCharactersControllerService::OnGetCharacterByNameReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                                   bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnGetCharacterByNameReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
	if (!ErrorMsg.IsEmpty())
	{
		//TODO RAISE ERROR
		return;
	}

	OnCharacterReceived.Broadcast(
		*UNetworkingFunctionLibrary::Native_GetStructFromJsonObject<FFullCharInfo>(JsonObject));
}

void UNetCharactersControllerService::GetCharacterByName(const FString& CharacterName, const FString& UserSession)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(FCharName{UserSession, CharacterName}, PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Characters/ByName",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnGetCharacterByNameReceived);
		return;
	}

	Debug::Print(TEXT("Logout Error serializing!"), this);
}
