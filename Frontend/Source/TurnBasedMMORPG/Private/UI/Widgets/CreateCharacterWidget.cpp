#include "UI/Widgets/CreateCharacterWidget.h"

#include "MMOGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Engine/GameInstance.h"
#include "Subsystems/NetAccountService.h"

void UCreateCharacterWidget::TryCreateCharacter()
{
	GetGameInstance()->GetSubsystem<UNetAccountService>()->CreateCharacter(
		Cast<UMMOGameInstance>(GetGameInstance())->GetUserSessionGUID(),
		NicknameText->GetText().ToString(),
		"MaleWarrior");
}

FOnButtonClickedEvent& UCreateCharacterWidget::OnCreateButtonClicked() const
{
	return CreateButton->OnClicked;
}

FOnButtonClickedEvent& UCreateCharacterWidget::OnCancelButtonClicked() const
{
	return CancelButton->OnClicked;
}

void UCreateCharacterWidget::NativeOnInitialized()
{
	Super::NativeConstruct();
	OnCreateButtonClicked().AddDynamic(this, &ThisClass::TryCreateCharacter);
}
