#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UI/MMOBaseWidget.h"
#include "ActionPointsWidget.generated.h"

class URichTextBlock;
class USpacer;
class UHorizontalBox;

USTRUCT()
struct FActionPointsItem
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UImage> Image;
	UPROPERTY()
	TObjectPtr<USpacer> Spacer;
};

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UActionPointsWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UPanelWidget> ActionPointsPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URichTextBlock> CountText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> ActionPointsTexture;

	UPROPERTY()
	TArray<FActionPointsItem> Items;

	int CurrentActionPoint;
	int MaxActionPoints;

	UPROPERTY(EditAnywhere)
	int CurrentPoints = 6;
	void Refresh();
	void SetCurrentAbilityPoints(const FOnAttributeChangeData& OnAttributeChangeData);
	void SetMaxAbilityPoints(const FOnAttributeChangeData& OnAttributeChangeData);

public:
	void CreateActionPoint();
	virtual void NativePreConstruct() override;


	virtual void SetOwningActor(AActor* InOwningActor) override;
};
