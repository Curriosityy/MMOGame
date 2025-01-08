#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "PlayerStatusBarWidget.generated.h"

class UStatusBarsWidget;
class UStatusBarWidget;
class UIconWidget;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UPlayerStatusBarWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UIconWidget> PlayerIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UStatusBarsWidget> PlayerStatusBars;

	virtual void NativePreConstruct() override;
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
