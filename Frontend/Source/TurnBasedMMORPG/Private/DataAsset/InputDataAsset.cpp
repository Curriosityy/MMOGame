// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/InputDataAsset.h"

UInputAction* UInputDataAsset::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FInputConfig& Action : NativeInputActions)
	{
		if(Action.InputTag == InInputTag)
		{
			return Action.InputAction;
		}
	}
	
	return nullptr;
}
