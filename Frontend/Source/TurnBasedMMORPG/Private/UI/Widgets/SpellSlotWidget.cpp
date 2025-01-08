#include "UI/Widgets/SpellSlotWidget.h"

#include "AbilitySystemComponent.h"
#include "DebugHelper.h"
#include "Messages.h"
#include "MMOPlayerState.h"
#include "Tags.h"
#include "AbilitySystem/MMOPlayerAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "Character/PlayerCharacter.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "UI/Widgets/IconWidget.h"
#include "UI/Widgets/ImageVisibleOnSet.h"

void USpellSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USpellSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshSlotImage();
}

void USpellSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void USpellSlotWidget::RefreshSlotImage() const
{
	Icon->Image->SetIconImage(CurrentAbility.Get() ? CurrentAbility->GetIcon() : nullptr);
}

void USpellSlotWidget::OnBarUpdated(const FGameplayTag& Tag, const UMMOBattleAbility* BattleAbility)
{
	if (Tag != InputTag)
	{
		return;
	}

	CurrentAbility = BattleAbility;

	RefreshSlotImage();
}

void USpellSlotWidget::Test(FGameplayTag Tag, const FBarUpdatedMessage& Message)
{
	Debug::Print("ASD", this);
}

void USpellSlotWidget::SetOwningActor(AActor* InOwningActor)
{
	Super::SetOwningActor(InOwningActor);


	UMMOPlayerAbilitySystemComponent* ac = Cast<UMMOPlayerAbilitySystemComponent>(
		Cast<IAbilitySystemInterface>(InOwningActor)->GetAbilitySystemComponent());

	FGameplayAbilitySpec* ability = ac->GetAbilitiesByDynamicTag(InputTag);

	if (ability)
	{
		CurrentAbility = Cast<UMMOBattleAbility>(ability->Ability);
	}


	ac->OnAbilityBind.AddUObject(this, &ThisClass::OnBarUpdated);

	RefreshSlotImage();
}
