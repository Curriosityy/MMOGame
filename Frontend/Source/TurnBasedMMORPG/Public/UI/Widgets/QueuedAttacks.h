#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "QueuedAttacks.generated.h"

struct FAttackStruct;
class UImage;
class USpacer;
/**
 * 
 */
USTRUCT()
struct FQueueItem
{
	GENERATED_BODY()

	FQueueItem() = default;

	FQueueItem(USpacer* InSpacer, UImage* InImage): Spacer(InSpacer), QueueImage(InImage)
	{
	}

	UPROPERTY()
	TObjectPtr<USpacer> Spacer;

	UPROPERTY()
	TObjectPtr<UImage> QueueImage;
};

UCLASS()
class TURNBASEDMMORPG_API UQueuedAttacks : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UPanelWidget> QueuePanel{};

	UPROPERTY()
	TArray<FQueueItem> Queue{};

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> DefaultTexture{};

	UPROPERTY(EditDefaultsOnly)
	int TestQueue{6};

	UFUNCTION()
	void OnQueueUpdated(const TArray<FAttackStruct>& AttackStructs);

public:
	//TODO REFACTOR
	void AddToQueue(TObjectPtr<UTexture2D> WidgetImage);

	virtual void NativePreConstruct() override;


	virtual void SetOwningActor(AActor* InOwningActor) override;
};
