#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "StatusBarWidget.generated.h"

class URichTextBlock;
class UTextBlock;
class USizeBox;
class UProgressBar;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UStatusBarWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USizeBox> SizeBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<URichTextBlock> TextValue;

	//TODO List of colors based on %
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget, AllowPrivateAccess))
	FLinearColor StatusBarColor;

	float CurrentValue;
	float MaxValue;

public:
	UFUNCTION(BlueprintCallable)
	virtual void RefreshPercentage();

	virtual void SetCurrentValue(const float InCurrentValue);
	virtual void SetMaxValue(const float InMaxValue);

	virtual void NativePreConstruct() override;
};
