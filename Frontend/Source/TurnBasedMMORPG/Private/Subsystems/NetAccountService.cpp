#include "Subsystems/NetAccountService.h"
#include "DebugHelper.h"
#include "JsonObjectConverter.h"
#include "NetworkingFunctionLibrary.h"

void UNetAccountService::LoginAndCreateSession(const FString& Login, const FString& Password)
{
	FString PostParameters = "";
	if (FJsonObjectConverter::UStructToJsonObjectString(FLoginDTO{Login, Password}, PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(GetAPIPath(),
		                                               "api/Users/LoginAndCreateSession",
		                                               GetAPICustomerKey(),
		                                               PostParameters,
		                                               this,
		                                               &UNetAccountService::OnLoginReceived);
		return;
	}

	Debug::Print(TEXT("LoginAndCreateSession Error serializing!"), this);
}

void UNetAccountService::OnRegisterReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                            bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnRegisterReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);

	if (!ErrorMsg.IsEmpty())
	{
		OnLoginFailed.Broadcast();
		return;
	}

	OnLoginSuccess.Broadcast(JsonObject->Values["UserSessionGuid"]->AsString());
}

void UNetAccountService::OnLoginReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                         bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnLoginReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);

	if (!ErrorMsg.IsEmpty())
	{
		OnLoginFailed.Broadcast();
		return;
	}


	OnLoginSuccess.Broadcast(JsonObject->Values["UserSessionGuid"]->AsString());
}

void UNetAccountService::OnLogoutReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                          bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnLogoutReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
}

void UNetAccountService::OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                              bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TArray<FCharacterBaseInfoDTO> CharacterInfos;
	UNetworkingFunctionLibrary::Native_GetTArrayUStructFromResponse(Response,
	                                                                bConnectedSuccessfully,
	                                                                "OnCharactersReceived",
	                                                                ErrorMsg,
	                                                                CharacterInfos);

	OnCharactersReceivedSuccess.Broadcast(CharacterInfos);
}

void UNetAccountService::OnCharacterSelectedReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                     bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnCharacterSelectedReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);

	if (!ErrorMsg.IsEmpty())
	{
		OnLoginFailed.Broadcast();
		return;
	}


	TSharedPtr<FCharacterFullInfoDTO> DTO = UNetworkingFunctionLibrary::Native_GetStructFromJsonObject<
		FCharacterFullInfoDTO>(JsonObject);

	OnCharacterSelected.Broadcast(*DTO);
}

void UNetAccountService::OnServerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                          bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnServerReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
	if (!ErrorMsg.IsEmpty())
	{
		OnLoginFailed.Broadcast();
		return;
	}

	const FString ServerIP = JsonObject->GetStringField(TEXT("serverip"));
	const FString Port = JsonObject->GetStringField(TEXT("port"));

	OnServerInfoReceived.Broadcast(ServerIP + ":" + Port.Left(4));
}

void UNetAccountService::OnUserSessionReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                               bool bConnectedSuccessfully)
{
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnUserSessionReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
	if (!ErrorMsg.IsEmpty())
	{
		OnLoginFailed.Broadcast();
		return;
	}
	TSharedPtr<FCharacterFullInfoDTO> DTO = UNetworkingFunctionLibrary::Native_GetStructFromJsonObject<
		FCharacterFullInfoDTO>(JsonObject);
	OnGetUserSession.Broadcast(*DTO);
}

void UNetAccountService::OnCharacterCreatedReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                    bool bConnectedSuccessfully)
{
	//TODO REFACTOR
	//GetJson + GetStruct From JSON Can be in single function
	FString ErrorMsg;
	TSharedPtr<FJsonObject> JsonObject;
	UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(Response,
	                                                             bConnectedSuccessfully,
	                                                             "OnCharacterCreatedReceived",
	                                                             ErrorMsg,
	                                                             JsonObject);
	if (!ErrorMsg.IsEmpty())
	{
		OnLoginFailed.Broadcast();
		return;
	}

	TSharedPtr<FCharacterBaseInfoDTO> DTO = UNetworkingFunctionLibrary::Native_GetStructFromJsonObject<
		FCharacterBaseInfoDTO>(JsonObject);

	OnCharacterCreated.Broadcast(*DTO);
}


void UNetAccountService::Register(const FString& Email, const FString& Password)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(FRegisterDTO{Email, Password}, PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Users/RegisterUser",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnRegisterReceived);
		return;
	}

	Debug::Print(TEXT("Register Error serializing!"), this);
}

void UNetAccountService::Logout(const FString& UserSessionGUID)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(FUserSessionDTO{UserSessionGUID}, PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Users/Logout",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnLogoutReceived);
		return;
	}

	Debug::Print(TEXT("Logout Error serializing!"), this);
}

void UNetAccountService::GetAllCharacters(const FString& UserSessionGUID)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(FUserSessionDTO{UserSessionGUID}, PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Users/GetAllCharacters",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnCharactersReceived);
		return;
	}

	Debug::Print(TEXT("Register Error serializing!"), this);
}

void UNetAccountService::SetCharacterSelected(const FString& CharacterName, const FString& SessionGUID)
{
	FString PostParameters = "";
	if (FJsonObjectConverter::UStructToJsonObjectString(FSelectCharacterDTO{SessionGUID, CharacterName},
	                                                    PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Users/SetSelectedCharacterAndGetUserSession",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnCharacterSelectedReceived);
		return;
	}

	Debug::Print(TEXT("Register Error serializing!"), this);
}

void UNetAccountService::GetServerToConnectTo(const FString& UserSessionGUID, const FString& CharacterName)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(
		FGetServerToConnectToDTO{UserSessionGUID, CharacterName, "GETLASTZONENAME", 0},
		PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Users/GetServerToConnectTo",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnServerReceived);
		return;
	}
	Debug::Print(TEXT("Register Error serializing!"), this);
}

void UNetAccountService::GetUserSessionInfo(const FString& UserSessionGUID)
{
	FString GetParameters = "?UserSessionGUID=" + UserSessionGUID;

	UNetworkingFunctionLibrary::Native_ProcessGET(
		GetAPIPath(),
		"api/Users/GetUserSession",
		GetAPICustomerKey(),
		GetParameters,
		this,
		&ThisClass::OnUserSessionReceived);
}

void UNetAccountService::CreateCharacter(const FString& UserSessionGUID, const FString& CharacterName,
                                         const FString& ClassName)
{
	FString PostParameters = "";

	if (FJsonObjectConverter::UStructToJsonObjectString(
		FCreateCharacterDTO{UserSessionGUID, CharacterName, ClassName},
		PostParameters))
	{
		UNetworkingFunctionLibrary::Native_ProcessPOST(
			GetAPIPath(),
			"api/Users/CreateCharacter",
			GetAPICustomerKey(),
			PostParameters,
			this,
			&ThisClass::OnCharacterCreatedReceived);
		return;
	}
	Debug::Print(TEXT("Register Error serializing!"), this);
}
