// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "AbilitiesSystem/Abilities/WarriorGameplayAbility.h"

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

void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& defaultWeaponAbilitySet, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& grantedWeaponAbilities)
{
	if(defaultWeaponAbilitySet.IsEmpty())
	{
		return;
	}

	for(const FWarriorHeroAbilitySet& weaponAbility : defaultWeaponAbilitySet)
	{
		if(!weaponAbility.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec abilitySpec(weaponAbility.AbilityToGrant);
		abilitySpec.SourceObject = GetAvatarActor();
		abilitySpec.Level = ApplyLevel;
		abilitySpec.GetDynamicSpecSourceTags().AddTag(weaponAbility.InputTag);
		
		grantedWeaponAbilities.AddUnique(GiveAbility(abilitySpec));
	}
}

void UWarriorAbilitySystemComponent::RemoveGrantedAbilitySpecHandles(TArray<FGameplayAbilitySpecHandle>& specHandlesToRemove)
{
	if(specHandlesToRemove.IsEmpty())
	{
		return;
	}

	for(const FGameplayAbilitySpecHandle& specHandle : specHandlesToRemove)
	{
		if(specHandle.IsValid())
		{
			ClearAbility(specHandle);
		}
	}

	specHandlesToRemove.Empty();
}
