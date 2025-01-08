#include "UI/Widgets/PlayerStatusBarWidget.h"

#include "UI/Widgets/IconWidget.h"
#include "UI/Widgets/StatusBarsWidget.h"

void UPlayerStatusBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPlayerStatusBarWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
	PlayerIcon->SetOwningActor(InOwningActor);
	PlayerStatusBars->SetOwningActor(InOwningActor);
}
