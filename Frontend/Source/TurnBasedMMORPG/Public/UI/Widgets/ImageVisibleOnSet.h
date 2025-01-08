#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "ImageVisibleOnSet.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UImageVisibleOnSet : public UImage
{
	GENERATED_BODY()

public:
	virtual void SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize) override;

	void SetIconImage(const TSoftObjectPtr<UTexture2D>& NewTexture);
};
