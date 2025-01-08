#include "UI/Widgets/StatusBarsWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "UI/Widgets/StatusBarWidget.h"
#include "MMOPlayerState.h"

void UStatusBarsWidget::SetHealth(const FOnAttributeChangeData& OnAttributeChangeData)
{
	HealthBarWidget->SetCurrentValue(OnAttributeChangeData.NewValue);
}

void UStatusBarsWidget::SetMaxHealth(const FOnAttributeChangeData& OnAttributeChangeData)
{
	HealthBarWidget->SetMaxValue(OnAttributeChangeData.NewValue);
}

void UStatusBarsWidget::SetCurrentMana(const FOnAttributeChangeData& OnAttributeChangeData)
{
	ManaBarWidget->SetCurrentValue(OnAttributeChangeData.NewValue);
}

void UStatusBarsWidget::SetMaxMana(const FOnAttributeChangeData& OnAttributeChangeData)
{
	ManaBarWidget->SetMaxValue(OnAttributeChangeData.NewValue);
}

void UStatusBarsWidget::SetStamina(const FOnAttributeChangeData& OnAttributeChangeData)
{
	StaminaBarWidget->SetCurrentValue(OnAttributeChangeData.NewValue);
}

void UStatusBarsWidget::SetMaxStamina(const FOnAttributeChangeData& OnAttributeChangeData)
{
	StaminaBarWidget->SetMaxValue(OnAttributeChangeData.NewValue);
}

void UStatusBarsWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);

	UAbilitySystemComponent* asc = Cast<IAbilitySystemInterface>(InOwningActor)->GetAbilitySystemComponent();

	HealthBarWidget->SetCurrentValue(asc->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute()));
	HealthBarWidget->SetMaxValue(asc->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute()));
	ManaBarWidget->SetCurrentValue(asc->GetNumericAttribute(UBaseAttributeSet::GetManaAttribute()));
	ManaBarWidget->SetMaxValue(asc->GetNumericAttribute(UBaseAttributeSet::GetMaxManaAttribute()));
	StaminaBarWidget->SetCurrentValue(asc->GetNumericAttribute(UBaseAttributeSet::GetStaminaAttribute()));
	StaminaBarWidget->SetMaxValue(asc->GetNumericAttribute(UBaseAttributeSet::GetMaxStaminaAttribute()));

	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(
		this, &ThisClass::SetHealth);
	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxHealthAttribute()).AddUObject(
		this, &ThisClass::SetMaxHealth);
	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetManaAttribute()).AddUObject(
		this, &ThisClass::SetCurrentMana);
	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxManaAttribute()).AddUObject(
		this, &ThisClass::SetMaxMana);
	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaminaAttribute()).AddUObject(
		this, &ThisClass::SetStamina);
	asc->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxStaminaAttribute()).AddUObject(
		this, &ThisClass::SetMaxStamina);
}
