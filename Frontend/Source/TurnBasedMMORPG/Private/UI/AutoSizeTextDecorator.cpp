#include "UI/AutoSizeTextDecorator.h"

#include "Components/PanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/RichTextBlock.h"
#include "Kismet/KismetMathLibrary.h"

bool FAutoSizeDecorator::Supports(const FTextRunParseResults& RunInfo, const FString& Text) const
{
	return true;
}

void FAutoSizeDecorator::CreateDecoratorText(const FTextRunInfo& RunInfo, FTextBlockStyle& InOutTextStyle,
                                             FString& InOutString) const
{
	FVector2D DeSize = Owner->GetDesiredSize();
	float minsize = UKismetMathLibrary::Min(DeSize.X, DeSize.Y);
	InOutTextStyle.SetFontSize(minsize);
	//InOutTextStyle.SetFontSize()
}

TSharedPtr<ITextDecorator> UAutoSizeTextDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	Decorator = MakeShared<FAutoSizeDecorator, ESPMode::ThreadSafe>(FAutoSizeDecorator(InOwner));
	return Decorator;
}
