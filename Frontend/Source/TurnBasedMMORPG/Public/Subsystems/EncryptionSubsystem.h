// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EncryptionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UEncryptionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	FString EncryptionKey;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	FString EncryptWithAES(FString StringToEncrypt);
	FString DecryptWithAES(FString StringToDecrypt);
	FString EncryptNameAndSessionGUID(const FString& String, const FString& SessionGUID);
	void DecryptNameAndSessionGUID(const FString& EncryptedData, FString& PlayerName, FString& SessionGUID);
};
