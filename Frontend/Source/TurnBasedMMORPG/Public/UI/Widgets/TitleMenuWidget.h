// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "TitleMenuWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API UTitleMenuWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UNamedSlot> MenuSlot;
};
