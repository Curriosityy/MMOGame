#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "QueueSpellWidget.generated.h"

class UImageVisibleOnSet;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UQueueSpellWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImageVisibleOnSet> Image;

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
