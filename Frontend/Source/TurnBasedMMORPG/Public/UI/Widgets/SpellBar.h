#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "SpellBar.generated.h"

class USpellSlotWidget;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API USpellBar : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellSlotWidget> SpellSlot1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellSlotWidget> SpellSlot2;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellSlotWidget> SpellSlot3;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellSlotWidget> SpellSlot4;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellSlotWidget> SpellSlot5;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USpellSlotWidget> SpellSlot6;

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
