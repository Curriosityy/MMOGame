#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "BattleToggleWidget.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UBattleToggleWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
