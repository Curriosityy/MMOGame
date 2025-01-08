// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MMOBaseWidget.generated.h"

class AMMOPlayerState;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetOwningActor(AActor* InOwningActor);
};
