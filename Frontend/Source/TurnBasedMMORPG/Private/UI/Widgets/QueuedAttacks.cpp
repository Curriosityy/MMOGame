#include "UI/Widgets/QueuedAttacks.h"

#include "MMOPlayerState.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "BattleSystem/BattleComponent.h"
#include "BattleSystem/BattleComponentInterface.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/Spacer.h"

void UQueuedAttacks::AddToQueue(TObjectPtr<UTexture2D> WidgetImage)
{
	UImage* apImage = WidgetTree->ConstructWidget<UImage>();
	QueuePanel->AddChild(apImage);
	USpacer* spacer = WidgetTree->ConstructWidget<USpacer>();
	spacer->SetSize({3, 3});
	QueuePanel->AddChild(spacer);
	apImage->SetBrushFromTexture(WidgetImage);
	Queue.Add({spacer, apImage});
}

void UQueuedAttacks::NativePreConstruct()
{
	Super::NativePreConstruct();
	//if (IsDesignTime())
	{
		Queue.Reset();
		QueuePanel->ClearChildren();
		for (int i = 0; i < TestQueue; i++)
		{
			AddToQueue(DefaultTexture);
		}
	}
}

void UQueuedAttacks::OnQueueUpdated(const TArray<FAttackStruct>& AttackStructs)
{
	int HowManyAdd = AttackStructs.Num() - Queue.Num();

	for (int i = 0; i < HowManyAdd; i++)
	{
		AddToQueue(DefaultTexture);
	}

	for (int i = 0; i < Queue.Num(); i++)
	{
		if (AttackStructs.Num() > i)
		{
			Queue[i].Spacer->SetVisibility(ESlateVisibility::Visible);
			Queue[i].QueueImage->SetBrushFromSoftTexture(AttackStructs[i].BattleAbility->GetIcon());
			Queue[i].QueueImage->SetVisibility(ESlateVisibility::Visible);
			continue;
		}

		Queue[i].Spacer->SetVisibility(ESlateVisibility::Hidden);
		Queue[i].QueueImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UQueuedAttacks::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);
	UBattleComponent* bs = Cast<IBattleComponentInterface>(InOwningActor)->GetBattleComponent();
	bs->OnQueueUpdated.AddUObject(this, &ThisClass::OnQueueUpdated);
	OnQueueUpdated(bs->GetQueue());
}
