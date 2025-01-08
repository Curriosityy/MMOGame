// Copyright 2023 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystems/NetAccountService.h"
#include "UI/MMOBaseWidget.h"
#include "CharacterButtonWidget.generated.h"

class FOnButtonClickedEvent;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS(Abstract)
class TURNBASEDMMORPG_API UCharacterButtonWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UButton> SelectButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UTextBlock> CharacterText;

	FString CharName;

	UFUNCTION()
	void OnCharacterSelected(const FCharacterFullInfoDTO& Character);
	UFUNCTION()
	void OnClicked();

public:
	FOnButtonClickedEvent& SelectButtonClickedEvent() const;

	void Setup(const FString& InCharName);


	virtual void NativeOnInitialized() override;

	virtual void SetOwningActor(AActor* InOwningActor) override;
};
