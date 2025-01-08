// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "GameModes/MMORPGGameMode.h"
#include "Subsystems/NetAccountService.h"
#include "Subsystems/NetCharactersControllerService.h"
#include "Subsystems/NetServerInstanceService.h"
#include "InGameGameMode.generated.h"

class AMMORPGCharacter;
class APlayerGameController;
/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FCharGUIDPair
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FString GUID;
	UPROPERTY(EditDefaultsOnly)
	FString Name;
};

UCLASS()
class TURNBASEDMMORPG_API AInGameGameMode : public AMMORPGGameMode
{
	GENERATED_BODY()

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	                              const FString& Options, const FString& Portal) override;

	int32 ZoneInstanceID;

	FZoneInstanceFullInfoDTO CurrentZoneInstanceInfo;

	UPROPERTY(EditDefaultsOnly)
	TArray<FCharGUIDPair> DefaultCharacters{};
	int CharToUse = 0;

	UFUNCTION()
	void ZoneInfoReceived(const FZoneInstanceFullInfoDTO& ZoneInstanceFullInfoDto);

	UPROPERTY()
	TMap<FString, APlayerController*> WaitingPlayers;
	UFUNCTION()
	void OnCharInfoReceived(const FFullCharInfo& FullCharInfo);

	UPROPERTY()
	TArray<APlayerGameController*> ConnectedPlayers{};

public:
	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	virtual void Logout(AController* Exiting) override;

	void SpawnSoftPawnAndPossess(const FTransform& SpawnPosition, const TSoftClassPtr<APawn>& PawnToSpawn,
	                             AController* Controller) const;
};
