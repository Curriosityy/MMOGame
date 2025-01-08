#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/CreateCharacterWidget.h"
#include "InGameHUD.generated.h"

class UInBattlePlayerCanvas;
class UUserWidget;
class UInGamePlayerCanvas;
class UPlayerStatusBarWidget;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

	bool bIsSetted = false;

	UPROPERTY()
	TObjectPtr<UInGamePlayerCanvas> PlayerStatusBar;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInGamePlayerCanvas> PlayerStatusBarSubclass;

public:
	virtual void BeginPlay() override;
	void ShowLoadScreen(bool bShow);
	void SetupBattleHUD(bool bShow);
	void SetupInGameHUD(bool bShow);
	virtual void OnRep_Owner() override;
	template <class WidgetClass>
	WidgetClass* SpawnWidgetAndAddToViewport(TSubclassOf<UUserWidget> WidgetToSpawn, ESlateVisibility Visibility,
	                                         int ViewportLayer);

	void SetPlayerState(class AMMOPlayerState* Pawn);
};


template <class WidgetClass>
WidgetClass* AInGameHUD::SpawnWidgetAndAddToViewport(TSubclassOf<UUserWidget> WidgetToSpawn,
                                                     ESlateVisibility Visibility, int ViewportLayer)
{
	static_assert(TIsDerivedFrom<WidgetClass, UUserWidget>::IsDerived, "WidgetClass must be derived from UUserWidget");
	WidgetClass* Widget = Cast<WidgetClass>(CreateWidget(GetWorld(), WidgetToSpawn));

	if (!Widget)
	{
		return nullptr;
	}

	Widget->AddToViewport(ViewportLayer);
	Widget->SetVisibility(Visibility);

	return Widget;
}
