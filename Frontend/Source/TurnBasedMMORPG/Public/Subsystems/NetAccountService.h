#pragma once

#include "CoreMinimal.h"
#include "MultiplayerNetworkConnectionSubsystem.h"
#include "NetAccountService.generated.h"

USTRUCT()
struct FRegisterDTO
{
	GENERATED_BODY()
	FRegisterDTO() = default;

	FRegisterDTO(const FString& InEmail, const FString& InPassword):
		Email(InEmail),
		Password(InPassword)
	{
	}

	UPROPERTY()
	FString Email;

	UPROPERTY()
	FString Password;
};

USTRUCT()
struct FLoginDTO
{
	GENERATED_BODY()
	FLoginDTO() = default;

	FLoginDTO(const FString& InLogin, const FString& InPassword):
		Login(InLogin),
		Password(InPassword)
	{
	}

	UPROPERTY()
	FString Login;

	UPROPERTY()
	FString Password;
};

USTRUCT()
struct FUserSessionDTO
{
	GENERATED_BODY()

	FUserSessionDTO() = default;

	FUserSessionDTO(const FString& InUserSessionGUID):
		UserSessionGUID(InUserSessionGUID)
	{
	}

	UPROPERTY()
	FString UserSessionGUID;
};

USTRUCT()
struct FSelectCharacterDTO
{
	GENERATED_BODY()

	FSelectCharacterDTO() = default;

	FSelectCharacterDTO(const FString& InUserSessionGUID, const FString& InSelectedCharacterName):
		UserSessionGUID(InUserSessionGUID), SelectedCharacterName(InSelectedCharacterName)
	{
	}

	UPROPERTY()
	FString UserSessionGUID;

	UPROPERTY()
	FString SelectedCharacterName;
};

USTRUCT()
struct FCharacterBaseInfoDTO
{
	GENERATED_BODY()

	FCharacterBaseInfoDTO() = default;

	FCharacterBaseInfoDTO(const int& InCharID, const FString& InCharName):
		CharacterName(InCharName)
	{
	}

	UPROPERTY()
	FString CharacterName;
};

USTRUCT()
struct FCharacterFullInfoDTO
{
	GENERATED_BODY()

	FCharacterFullInfoDTO() = default;

	FCharacterFullInfoDTO(const FString& InUserSessionGUID,
	                      const int& InCharacterID,
	                      const FString& InCharName,
	                      const FString& InZoneName,
	                      const double InX,
	                      const double InY,
	                      const double InZ,
	                      const double InRX,
	                      const double InRY,
	                      const double InRZ):
		UserSessionGUID(InUserSessionGUID),
		CharacterID(InCharacterID),
		CharName(InCharName),
		ZoneName(InZoneName),
		X(InX),
		Y(InY),
		Z(InZ),
		Rx(InRX),
		Ry(InRY),
		Rz(InRZ)
	{
	}

	UPROPERTY()
	FString UserSessionGUID;

	UPROPERTY()
	int CharacterID;
	UPROPERTY()
	FString CharName;
	UPROPERTY()
	FString ZoneName;
	UPROPERTY()
	double X;
	UPROPERTY()
	double Y;
	UPROPERTY()
	double Z;
	UPROPERTY()
	double Rx;
	UPROPERTY()
	double Ry;
	UPROPERTY()
	double Rz;
};

USTRUCT()
struct FGetServerToConnectToDTO
{
	GENERATED_BODY()

	FGetServerToConnectToDTO() = default;

	FGetServerToConnectToDTO(const FString& InUserSessionGUID, const FString& InCharacterName,
	                         const FString& InZoneName, const int InPlayerGroupType):
		UserSessionGUID(InUserSessionGUID),
		CharacterName(InCharacterName),
		ZoneName(InZoneName),
		PlayerGroupType(InPlayerGroupType)
	{
	}

	UPROPERTY()
	FString UserSessionGUID;
	UPROPERTY()
	FString CharacterName;
	UPROPERTY()
	FString ZoneName;
	UPROPERTY()
	int PlayerGroupType;
};

USTRUCT()
struct FCreateCharacterDTO
{
	GENERATED_BODY()

	FCreateCharacterDTO() = default;

	FCreateCharacterDTO(const FString& InUserSessionGUID, const FString& InCharacterName, const FString& InClassName)
		: UserSessionGUID(InUserSessionGUID),
		  CharacterName(InCharacterName),
		  ClassName(InClassName)
	{
	}

	UPROPERTY()
	FString UserSessionGUID;
	UPROPERTY()
	FString CharacterName;
	UPROPERTY()
	FString ClassName;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginSuccess, const FString&, UsserSessionGUID);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharactersRecieved, const TArray<FCharacterBaseInfoDTO>&,
                                            Characters);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterCreated, const FCharacterBaseInfoDTO&,
                                            Character);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoginFailed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, const FCharacterFullInfoDTO&,
                                            Character);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetUserSession, const FCharacterFullInfoDTO&,
                                            Character);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnServerInfoReceived, const FString&,
                                            IpAndPort);

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UNetAccountService : public UMultiplayerNetworkConnectionSubsystem
{
	GENERATED_BODY()

protected:
	void OnRegisterReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                        bool bConnectedSuccessfully);
	void OnLoginReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                     bool bConnectedSuccessfully);
	void OnLogoutReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                      bool bConnectedSuccessfully);
	void OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                          bool bConnectedSuccessfully);
	void OnCharacterSelectedReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                                 bool bConnectedSuccessfully);
	void OnServerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                      bool bConnectedSuccessfully);

	void OnUserSessionReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                           bool bConnectedSuccessfully);

	void OnCharacterCreatedReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                                bool bConnectedSuccessfully);

public:
	void LoginAndCreateSession(const FString& Login, const FString& Password);
	void Register(const FString& Email, const FString& Password);
	void Logout(const FString& UserSessionGUID);
	void GetAllCharacters(const FString& UserSessionGUID);
	void SetCharacterSelected(const FString& CharacterName, const FString& Session);
	void GetServerToConnectTo(const FString& UserSessionGUID, const FString& CharacterName);
	void GetUserSessionInfo(const FString& UserSessionGUID);
	void CreateCharacter(const FString& UserSessionGUID, const FString& CharacterName, const FString& ClassName);
	//TODO:Move to GameplayMessageRouter
	FOnLoginSuccess OnLoginSuccess;
	FOnLoginFailed OnLoginFailed;
	FOnCharactersRecieved OnCharactersReceivedSuccess;
	FOnCharacterSelected OnCharacterSelected;
	FOnServerInfoReceived OnServerInfoReceived;
	FOnGetUserSession OnGetUserSession;
	FOnCharacterCreated OnCharacterCreated;
};
