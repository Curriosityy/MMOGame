#include "UI/Widgets/ActionPointsWidget.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/RichTextBlock.h"
#include "Components/Spacer.h"
#include "MMOPlayerState.h"

void UActionPointsWidget::CreateActionPoint()
{
	UImage* apImage = WidgetTree->ConstructWidget<UImage>();
	ActionPointsPanel->AddChild(apImage);
	USpacer* spacer = WidgetTree->ConstructWidget<USpacer>();
	spacer->SetSize({3, 3});
	ActionPointsPanel->AddChild(spacer);
	apImage->SetBrushFromTexture(ActionPointsTexture);

	Items.Add({apImage, spacer});
}

void UActionPointsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ActionPointsPanel && ActionPointsTexture && IsDesignTime())
	{
		ActionPointsPanel->ClearChildren();
		Items.Reset();

		for (int i = 0; i < 6; i++)
		{
			CreateActionPoint();
		}
	}
}

void UActionPointsWidget::Refresh()
{
	const FString Text = FString::Printf(TEXT("%i / %i"), CurrentActionPoint, MaxActionPoints);
	CountText->SetText(FText::FromString(Text));

	int needActionPoints = MaxActionPoints - Items.Num();

	for (int i = 0; i < needActionPoints; i++)
	{
		CreateActionPoint();
	}

	for (int i = 0; i < Items.Num(); i++)
	{
		if (i < CurrentActionPoint)
		{
			Items[i].Image->SetVisibility(ESlateVisibility::Visible);
			Items[i].Spacer->SetVisibility(ESlateVisibility::Visible);
			continue;
		}

		Items[i].Image->SetVisibility(ESlateVisibility::Hidden);
		Items[i].Spacer->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UActionPointsWidget::SetCurrentAbilityPoints(const FOnAttributeChangeData& OnAttributeChangeData)
{
	CurrentActionPoint = OnAttributeChangeData.NewValue;
	Refresh();
}

void UActionPointsWidget::SetMaxAbilityPoints(const FOnAttributeChangeData& OnAttributeChangeData)
{
	MaxActionPoints = OnAttributeChangeData.NewValue;
	Refresh();
}

void UActionPointsWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);

	UAbilitySystemComponent* asc = Cast<IAbilitySystemInterface>(InOwningActor)->GetAbilitySystemComponent();

	CurrentActionPoint = asc->GetNumericAttribute(UBaseAttributeSet::GetCurrentAbilityPointsAttribute());
	MaxActionPoints = asc->GetNumericAttribute(UBaseAttributeSet::GetMaxAbilityPointsAttribute());

	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetCurrentAbilityPointsAttribute()).AddUObject(
		this, &ThisClass::SetCurrentAbilityPoints);
	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxAbilityPointsAttribute()).AddUObject(
		this, &ThisClass::SetMaxAbilityPoints);

	Refresh();
}
