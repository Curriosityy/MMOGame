// Copyright 2023 Sabre Dart Studios


#include "NetworkingFunctionLibrary.h"

#include "DebugHelper.h"

void UNetworkingFunctionLibrary::Native_GetJsonObjectFromResponse(const FHttpResponsePtr& Response,
                                                                  const bool bWasSuccessful,
                                                                  const FString& CallingMethodName,
                                                                  FString& ErrorMsg,
                                                                  TSharedPtr<FJsonObject>& JsonObject)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		Debug::Print(FString::Printf(TEXT("%s - Response was unsuccessful or invalid!"), *CallingMethodName), GWorld);
		ErrorMsg = CallingMethodName + " - Response was unsuccessful or invalid!";
		return;
	}

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		Debug::Print(FString::Printf(TEXT("%s - Error Deserializing JsonObject!"), *CallingMethodName), GWorld);
		ErrorMsg = CallingMethodName + " - Error Deserializing JsonObject!";
		return;
	}

	if (Response->GetResponseCode() >= 300)
	{
		Debug::Print(
			FString::Printf(
				TEXT("%s - Response Code is %i! Payload: \n %s"), *CallingMethodName, Response->GetResponseCode(),
				*Response->GetContentAsString()), GWorld);
		ErrorMsg = FString::Printf(
			TEXT("%s - Response Code is %i! Payload: \n %s"), *CallingMethodName, Response->GetResponseCode(),
			*Response->GetContentAsString());
		return;
	}

	ErrorMsg = "";
}
