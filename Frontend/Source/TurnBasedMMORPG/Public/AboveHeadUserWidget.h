#pragma once

#include "CoreMinimal.h"
#include "UI/MMOBaseWidget.h"
#include "AboveHeadUserWidget.generated.h"

class UStatusBarsWidget;
class URichTextBlock;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UAboveHeadUserWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<URichTextBlock> NicknameText;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UStatusBarsWidget> StatusBars;

	bool IsInitialized = false;

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
