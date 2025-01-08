#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "UI/MMOBaseWidget.h"
#include "SpellSlotWidget.generated.h"

class UMMOBattleAbility;
struct FBarUpdatedMessage;
class URichTextBlock;
class UIconWidget;
/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API USpellSlotWidget : public UMMOBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UIconWidget> Icon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<URichTextBlock> RichText;

	UPROPERTY(EditAnywhere, meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	FGameplayMessageListenerHandle MessageListener;

	UPROPERTY(EditAnywhere, meta=(Categories="InputTag"))
	TWeakObjectPtr<const UMMOBattleAbility> CurrentAbility;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
	void RefreshSlotImage() const;

	UFUNCTION()
	void OnBarUpdated(const FGameplayTag& Tag, const UMMOBattleAbility* BattleAbility);
	UFUNCTION()
	void Test(FGameplayTag Tag, const FBarUpdatedMessage& Message);

public:
	virtual void SetOwningActor(AActor* InOwningActor) override;
};
