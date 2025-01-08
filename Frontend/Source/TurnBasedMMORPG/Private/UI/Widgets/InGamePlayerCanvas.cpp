#include "UI/Widgets/InGamePlayerCanvas.h"

#include "UI/Widgets/ActionPointsWidget.h"
#include "UI/Widgets/PlayerStatusBarWidget.h"
#include "UI/Widgets/QueuedAttacks.h"
#include "UI/Widgets/SpellBar.h"

void UInGamePlayerCanvas::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
	PlayerStatusBar->SetOwningActor(InOwningActor);
	QueuedAttacksBar->SetOwningActor(InOwningActor);
	SpellBar->SetOwningActor(InOwningActor);
	ActionPointsWidget->SetOwningActor(InOwningActor);
}
