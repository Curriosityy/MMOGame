#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "InGamePlayerCanvas.generated.h"

class UActionPointsWidget;
class USpellBar;
class UQueuedAttacks;
class UCanvasPanel;
class UPlayerStatusBarWidget;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UInGamePlayerCanvas : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UPlayerStatusBarWidget> PlayerStatusBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UQueuedAttacks> QueuedAttacksBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellBar> SpellBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UActionPointsWidget> ActionPointsWidget;

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
