// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& inputTag)
{
	if(!inputTag.IsValid())
	{
		return;
	}

	for(const FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities())
	{
		if(!abilitySpec.GetDynamicSpecSourceTags().HasTagExact(inputTag))
		{
			continue;
		}
		TryActivateAbility(abilitySpec.Handle);
	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& inputTag)
{
}
