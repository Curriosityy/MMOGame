#include "UI/Widgets/IconWidget.h"

#include "Components/SizeBox.h"
#include "UI/Widgets/ImageVisibleOnSet.h"

void UIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Image)
	{
		//Image->SetIconImage(IsDesignTime() ? PreviewTexture : nullptr);
		Image->SetIconImage(PreviewTexture);
	}

	// if (SizeBox && SizeBoxSize > 0)
	// {
	// 	SizeBox->SetWidthOverride(SizeBoxSize);
	// 	SizeBox->SetHeightOverride(SizeBoxSize);
	// }
}

void UIconWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
}
