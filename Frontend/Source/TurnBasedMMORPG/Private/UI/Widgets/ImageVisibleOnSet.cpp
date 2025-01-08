#include "UI/Widgets/ImageVisibleOnSet.h"

void UImageVisibleOnSet::SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize)
{
	Super::SetBrushFromTexture(Texture, bMatchSize);
	SetVisibility(ESlateVisibility::Visible);
}

void UImageVisibleOnSet::SetIconImage(const TSoftObjectPtr<UTexture2D>& NewTexture)
{
	if (!NewTexture.IsPending() && !NewTexture.IsValid())
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	SetBrushFromSoftTexture(NewTexture, true);
}
