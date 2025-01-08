#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "CreateCharacterWidget.generated.h"

class FOnButtonClickedEvent;
class UButton;
class UEditableText;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API UCreateCharacterWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UEditableText> NicknameText;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UButton> CreateButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UButton> CancelButton;

	UFUNCTION()
	void TryCreateCharacter();

public:
	FOnButtonClickedEvent& OnCreateButtonClicked() const;
	FOnButtonClickedEvent& OnCancelButtonClicked() const;


	virtual void NativeOnInitialized() override;
};
