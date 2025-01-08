#include "UI/InGameHUD.h"

#include "DebugHelper.h"
#include "MMOPlayerState.h"
#include "UI/Widgets/InBattlePlayerCanvas.h"
#include "UI/Widgets/InGamePlayerCanvas.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerStatusBarSubclass)
	{
		PlayerStatusBar = SpawnWidgetAndAddToViewport<UInGamePlayerCanvas>(
			PlayerStatusBarSubclass, ESlateVisibility::Visible, 1);
	}
}

void AInGameHUD::ShowLoadScreen(bool bShow)
{
	Debug::Print("AInGameHUD::ShowLoadScreen Not implemented", this);
}

void AInGameHUD::SetupBattleHUD(bool bShow)
{
	//PlayerBattleBar->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AInGameHUD::SetupInGameHUD(bool bShow)
{
	PlayerStatusBar->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AInGameHUD::OnRep_Owner()
{
	Super::OnRep_Owner();
}

void AInGameHUD::SetPlayerState(AMMOPlayerState* Pawn)
{
	if (bIsSetted)
	{
		return;
	}

	if (PlayerStatusBar)
	{
		PlayerStatusBar->SetOwningActor(Pawn);
		bIsSetted = true;
	}
}
