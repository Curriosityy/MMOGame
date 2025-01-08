#pragma once
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/GameViewportClient.h"

namespace Debug
{
	static void Print(const FString& Msg, const UObject* WorldContextObject,
	                  const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1,
	                  float TimeToDisplay = 5.f)
	{
		if (GEngine)
		{
			FString info = "";
			if (WorldContextObject)
			{
				info = WorldContextObject->GetWorld()->GetNetMode() != NM_Client
					       ? "Server"
					       : "Client";
			}

			GEngine->AddOnScreenDebugMessage(InKey, TimeToDisplay, Color, info + " :: " + Msg);
			UE_LOG(LogTemp, Display, TEXT("%s :: %s"), *info, *Msg);
		}
	}
}
