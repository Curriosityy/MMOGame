// Copyright 2023 Sabre Dart Studios


#include "Subsystems/EncryptionSubsystem.h"

#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/AES.h"
#include "Misc/ConfigCacheIni.h"

void UEncryptionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("OWSEncryptionKey"),
		EncryptionKey,
		GGameIni
	);
}

FString UEncryptionSubsystem::EncryptWithAES(FString StringToEncrypt)
{
	if (StringToEncrypt.IsEmpty())
	{
		return "";
	}
	if (EncryptionKey.IsEmpty())
	{
		return "";
	}

	FString SplitSymbol = "OWS#@!";
	StringToEncrypt.Append(SplitSymbol);

	EncryptionKey = FMD5::HashAnsiString(*EncryptionKey);
	TCHAR* KeyTChar = EncryptionKey.GetCharArray().GetData();

	uint32 Size = StringToEncrypt.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	uint8* ByteString = new uint8[Size];

	if (StringToBytes(StringToEncrypt, ByteString, Size))
	{
		FAES::EncryptData(ByteString, Size, StringCast<ANSICHAR>((KeyTChar)).Get());
		StringToEncrypt = FString::FromHexBlob(ByteString, Size);

		delete[] ByteString;
		return StringToEncrypt;
	}

	delete[] ByteString;
	return "";
}

FString UEncryptionSubsystem::DecryptWithAES(FString StringToDecrypt)
{
	if (StringToDecrypt.IsEmpty())
	{
		return "";
	}
	if (EncryptionKey.IsEmpty())
	{
		return "";
	}

	FString SplitSymbol = "OWS#@!";

	EncryptionKey = FMD5::HashAnsiString(*EncryptionKey);
	TCHAR* KeyTChar = EncryptionKey.GetCharArray().GetData();

	uint32 Size = StringToDecrypt.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	uint8* ByteString = new uint8[Size];

	if (FString::ToHexBlob(StringToDecrypt, ByteString, Size))
	{
		FAES::DecryptData(ByteString, Size, StringCast<ANSICHAR>((KeyTChar)).Get());
		StringToDecrypt = BytesToString(ByteString, Size);

		FString LeftPart;
		FString RightPart;
		StringToDecrypt.Split(SplitSymbol, &LeftPart, &RightPart, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		StringToDecrypt = LeftPart;

		delete[] ByteString;
		return StringToDecrypt;
	}

	delete[] ByteString;
	return "";
}

FString UEncryptionSubsystem::EncryptNameAndSessionGUID(const FString& PlayerName, const FString& SessionGUID)
{
	const FString Data = FGenericPlatformHttp::UrlEncode(PlayerName) + "|" + SessionGUID;
	return EncryptWithAES(Data);
}

void UEncryptionSubsystem::DecryptNameAndSessionGUID(const FString& EncryptedData, FString& PlayerName,
                                                     FString& SessionGUID)
{
	FString DecodedIDData = FGenericPlatformHttp::UrlDecode(DecryptWithAES(EncryptedData));
	TArray<FString> SplitArray;
	DecodedIDData.ParseIntoArray(SplitArray, TEXT("|"), false);
	checkf(SplitArray.Num()>=2, TEXT("Invalid Encryption Key"));
	PlayerName = SplitArray[0];
	SessionGUID = SplitArray[1];
}
