// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameStructs.h"
#include "DataAsset/InputDataAsset.h"
#include "MMOInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDMMORPG_API UMMOInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UInputDataAsset* InputConfig, const FGameplayTag& InInputTag,
	                           ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UInputDataAsset* InputConfig, UserObject* ContextObject,
	                            CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UMMOInputComponent::BindNativeInputAction(const UInputDataAsset* InputConfig,
                                               const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
                                               UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InputConfig, TEXT("Input config data asset is null"));

	UInputAction* InputAction = InputConfig->FindNativeInputActionByTag(InInputTag);

	if (!InputAction)
	{
		return;
	}

	BindAction(InputAction, TriggerEvent, ContextObject, Func);
}

template <class UserObject, typename CallbackFunc>
void UMMOInputComponent::BindAbilityInputAction(const UInputDataAsset* InputConfig, UserObject* ContextObject,
                                                CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InputConfig, TEXT("Input config data asset is null"));

	for (const FInputConfig& AbilityInputAction : InputConfig->AbilityInputActions)
	{
		if (!AbilityInputAction.IsValid())
		{
			continue;
		}

		BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc,
		           AbilityInputAction.InputTag);

		BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc,
		           AbilityInputAction.InputTag);
	}
}
