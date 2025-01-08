#include "UI/Widgets/SpellBar.h"

#include "UI/Widgets/SpellSlotWidget.h"

void USpellBar::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
	SpellSlot1->SetOwningActor(InOwningActor);
	SpellSlot2->SetOwningActor(InOwningActor);
	SpellSlot3->SetOwningActor(InOwningActor);
	SpellSlot4->SetOwningActor(InOwningActor);
	SpellSlot5->SetOwningActor(InOwningActor);
	SpellSlot6->SetOwningActor(InOwningActor);
}
