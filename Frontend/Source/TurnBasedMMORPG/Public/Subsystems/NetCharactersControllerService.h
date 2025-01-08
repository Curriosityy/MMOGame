// 

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerNetworkConnectionSubsystem.h"
#include "NetCharactersControllerService.generated.h"

/**
 * 
 */

USTRUCT()
struct FCharacterData
{
	GENERATED_BODY()
	UPROPERTY()
	FString CustomerGuid;
	UPROPERTY()
	int CharacterId;
	UPROPERTY()
	FString UserGuid;
	UPROPERTY()
	bool IsAdmin;
	UPROPERTY()
	bool IsModerator;
	UPROPERTY()
	FString CharacterName;
	UPROPERTY()
	FString mapName;
	UPROPERTY()
	float X;
	UPROPERTY()
	float Y;
	UPROPERTY()
	float Z;
	UPROPERTY()
	float RX;
	UPROPERTY()
	float RY;
	UPROPERTY()
	float RZ;
	UPROPERTY()
	FString ServerIP;
	UPROPERTY()
	FDateTime LastActivity;
	UPROPERTY()
	int CharacterLevel;
	UPROPERTY()
	int Exp;
	UPROPERTY()
	int Gender;
	UPROPERTY()
	int MaxHealth;
	UPROPERTY()
	int Health;
	UPROPERTY()
	int MaxMana;
	UPROPERTY()
	int Mana;
	UPROPERTY()
	int Stamina;
	UPROPERTY()
	int MaxStamina;
	UPROPERTY()
	int Strength;
	UPROPERTY()
	int Dexterity;
	UPROPERTY()
	int Intelligence;
	UPROPERTY()
	int Wisdom;
	UPROPERTY()
	int Faith;
	UPROPERTY()
	int Charisma;
	UPROPERTY()
	int MaxAbilityPoints;
	UPROPERTY()
	float Alignment;
	UPROPERTY()
	FString DefaultPawnClassPath;
	UPROPERTY()
	bool isInternalNetworkTestUser;
	UPROPERTY()
	int ClassId;
	UPROPERTY()
	FString BaseMesh;
	UPROPERTY()
	FString Port;
	UPROPERTY()
	int MapInstanceID;
	UPROPERTY()
	FString ClassName;
};


USTRUCT()
struct FFullCharInfo
{
	GENERATED_BODY()
	UPROPERTY()
	FString UserSessionGUID;

	UPROPERTY()
	FCharacterData CharacterData;
};

USTRUCT()
struct FCharName
{
	GENERATED_BODY()

	UPROPERTY()
	FString UserSessionGUID;

	UPROPERTY()
	FString CharacterName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterReceived, const FFullCharInfo&, FullCharInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnError);

UCLASS()
class TURNBASEDMMORPG_API UNetCharactersControllerService : public UMultiplayerNetworkConnectionSubsystem
{
	GENERATED_BODY()

	void OnGetCharacterByNameReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                                  bool bConnectedSuccessfully);

public:
	void GetCharacterByName(const FString& CharacterName, const FString& UserSession);

	FOnCharacterReceived OnCharacterReceived;
};
