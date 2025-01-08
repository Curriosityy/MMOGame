// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NetworkingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UNetworkingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	static TSharedPtr<T> Native_GetStructFromJsonObject(TSharedPtr<FJsonObject> JsonObject);

	static void Native_GetJsonObjectFromResponse(const FHttpResponsePtr& Response,
	                                             bool bWasSuccessful,
	                                             const FString& CallingMethodName,
	                                             FString& ErrorMsg,
	                                             TSharedPtr<FJsonObject>& JsonObject);


	template <class UserObject, typename CallbackFunc>
	static void Native_ProcessPOST(const FString& ApiModuleToCall,
	                               const FString& ApiToCall,
	                               const FString& APICustomerKey,
	                               const FString& PostParameters,
	                               UserObject* ContextObject,
	                               CallbackFunc FuncOnRequestComplete);
	template <class UserObject, class CallbackFunc>
	static void Native_ProcessGET(const FString& ApiModuleToCall, const FString& ApiToCall,
	                              const FString& APICustomerKey,
	                              const FString& PostParameters, UserObject* ContextObject,
	                              CallbackFunc FuncOnRequestComplete);

	template <class UserObject>
	static void Native_GetTArrayUStructFromResponse(const FHttpResponsePtr& Response,
	                                                bool bWasSuccessful,
	                                                const FString& CallingMethodName,
	                                                FString& ErrorMsg,
	                                                TArray<UserObject>& ArrayOutput);
};

template <typename T>
TSharedPtr<T> UNetworkingFunctionLibrary::Native_GetStructFromJsonObject(TSharedPtr<FJsonObject> JsonObject)
{
	TSharedPtr<T> Result = MakeShareable(new T);
	FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), T::StaticStruct(), Result.Get(), 0, 0);
	return Result;
}

template <class UserObject, typename CallbackFunc>
void UNetworkingFunctionLibrary::Native_ProcessPOST(const FString& ApiModuleToCall,
                                                    const FString& ApiToCall,
                                                    const FString& APICustomerKey,
                                                    const FString& PostParameters,
                                                    UserObject* ContextObject,
                                                    CallbackFunc FuncOnRequestComplete)
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(ContextObject, FuncOnRequestComplete);
	Request->SetURL(FString(ApiModuleToCall + ApiToCall));
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetHeader(TEXT("X-CustomerGUID"), APICustomerKey);
	Request->SetContentAsString(PostParameters);
	Request->ProcessRequest();
}

template <class UserObject, typename CallbackFunc>
void UNetworkingFunctionLibrary::Native_ProcessGET(const FString& ApiModuleToCall,
                                                   const FString& ApiToCall,
                                                   const FString& APICustomerKey,
                                                   const FString& GetParameters,
                                                   UserObject* ContextObject,
                                                   CallbackFunc FuncOnRequestComplete)
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(ContextObject, FuncOnRequestComplete);
	Request->SetURL(FString(ApiModuleToCall + ApiToCall + GetParameters));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetHeader(TEXT("X-CustomerGUID"), APICustomerKey);
	Request->ProcessRequest();
}

template <class UserObject>
void UNetworkingFunctionLibrary::Native_GetTArrayUStructFromResponse(const FHttpResponsePtr& Response,
                                                                     bool bWasSuccessful,
                                                                     const FString& CallingMethodName,
                                                                     FString& ErrorMsg,
                                                                     TArray<UserObject>& ArrayOutput)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		Debug::Print(FString::Printf(TEXT("%s - Response was unsuccessful or invalid!"), *CallingMethodName), GWorld);
		ErrorMsg = CallingMethodName + " - Response was unsuccessful or invalid!";
		return;
	}

	if (FJsonObjectConverter::JsonArrayStringToUStruct(Response->GetContentAsString(), &ArrayOutput, 0, 0))
	{
		ErrorMsg = "";
		return;
	}

	Debug::Print(FString::Printf(TEXT("%s - Error Deserializing JsonObject!"), *CallingMethodName), GWorld);
	ErrorMsg = CallingMethodName + " - Error Deserializing JsonObject!";
}
