#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "IconWidget.generated.h"

class UImageVisibleOnSet;
class UImage;
class USizeBox;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UIconWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USizeBox> SizeBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UImageVisibleOnSet> Image;

	UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess))
	TSoftObjectPtr<UTexture2D> PreviewTexture = {};

	virtual void NativePreConstruct() override;

	virtual void SetOwningActor(AActor* InOwningActor) override;
};
