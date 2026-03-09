// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& inInputTag) const
{
	for(const FWarriorInputActionConfig& inputConfig : NativeInputActions)
	{
		if(inputConfig.InputTag == inInputTag && inputConfig.InputAction)
		{
			return inputConfig.InputAction;
		}
	}
	return nullptr;
}
