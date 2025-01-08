#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "UI/MMOBaseWidget.h"
#include "StatusBarsWidget.generated.h"

class USizeBox;
class UStatusBarWidget;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UStatusBarsWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<USizeBox> SizeBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UStatusBarWidget> HealthBarWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UStatusBarWidget> ManaBarWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	TObjectPtr<UStatusBarWidget> StaminaBarWidget;


	void SetHealth(const FOnAttributeChangeData& OnAttributeChangeData);
	void SetMaxHealth(const FOnAttributeChangeData& OnAttributeChangeData);
	void SetCurrentMana(const FOnAttributeChangeData& OnAttributeChangeData);
	void SetMaxMana(const FOnAttributeChangeData& OnAttributeChangeData);
	void SetStamina(const FOnAttributeChangeData& OnAttributeChangeData);
	void SetMaxStamina(const FOnAttributeChangeData& OnAttributeChangeData);

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
