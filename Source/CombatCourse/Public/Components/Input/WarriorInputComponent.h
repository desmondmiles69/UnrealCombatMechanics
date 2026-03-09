// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMBATCOURSE_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* inInputConfig, const FGameplayTag& inInputTag, ETriggerEvent triggerEvent, UserObject* contextObject, CallbackFunc func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* inInputConfig, UserObject* contextObject, CallbackFunc inputPressedFunc, CallbackFunc inputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* inInputConfig, const FGameplayTag& inInputTag, ETriggerEvent triggerEvent, UserObject* contextObject, CallbackFunc func)
{
	 checkf(inInputConfig, TEXT("Input config data asset in null, cannot procees with binding"));

	if(UInputAction* foundInputAction = inInputConfig->FindNativeInputActionByTag(inInputTag))
	{
		BindAction(foundInputAction, triggerEvent, contextObject, func);
	}
}

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* inInputConfig, UserObject* contextObject, CallbackFunc inputPressedFunc, CallbackFunc inputReleasedFunc)
{
	checkf(inInputConfig, TEXT("Input config data asset in null, cannot procees with binding"));
	for(const FWarriorInputActionConfig& abilityInputActionConfig : inInputConfig->AbilityInputActions)
	{
		if(!abilityInputActionConfig.IsValid())
		{
			continue;
		}
		BindAction(abilityInputActionConfig.InputAction, ETriggerEvent::Started, contextObject, inputPressedFunc, abilityInputActionConfig.InputTag);
		BindAction(abilityInputActionConfig.InputAction, ETriggerEvent::Completed, contextObject, inputReleasedFunc, abilityInputActionConfig.InputTag);
	}
}
