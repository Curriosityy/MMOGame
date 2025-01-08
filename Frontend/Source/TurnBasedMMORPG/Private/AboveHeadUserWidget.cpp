#include "AboveHeadUserWidget.h"

#include "DebugHelper.h"
#include "MMOPlayerState.h"
#include "Components/RichTextBlock.h"
#include "GameFramework/Pawn.h"
#include "UI/Widgets/StatusBarsWidget.h"

void UAboveHeadUserWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);

	if (IsInitialized)
	{
		return;
	}

	Debug::Print(InOwningActor->GetActorLabel(), this);
	StatusBars->SetOwningActor(InOwningActor);

	NicknameText->SetText(FText::FromString(InOwningActor->GetHumanReadableName()));

	IsInitialized = true;
}
