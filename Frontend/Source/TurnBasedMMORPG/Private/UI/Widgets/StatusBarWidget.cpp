#include "UI/Widgets/StatusBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "Components/SizeBox.h"

void UStatusBarWidget::RefreshPercentage()
{
	ProgressBar->SetPercent(MaxValue / CurrentValue);
	const FString Text = FString::Printf(TEXT("%i / %i"), static_cast<int>(CurrentValue), static_cast<int>(MaxValue));
	TextValue->SetText(FText::FromString(Text));
}

void UStatusBarWidget::SetCurrentValue(const float InCurrentValue)
{
	CurrentValue = InCurrentValue;
	RefreshPercentage();
}

void UStatusBarWidget::SetMaxValue(const float InMaxValue)
{
	MaxValue = InMaxValue;
	RefreshPercentage();
}

void UStatusBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ProgressBar)
	{
		ProgressBar->SetFillColorAndOpacity(StatusBarColor);
	}
}
