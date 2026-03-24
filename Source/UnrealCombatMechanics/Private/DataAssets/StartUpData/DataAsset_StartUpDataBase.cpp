// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "AbilitiesSystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 applyLevel)
{
	check(InWarriorASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InWarriorASCToGive, applyLevel);
	GrantAbilities(ReactiveAbilities, InWarriorASCToGive, applyLevel);
	
	for (const TSubclassOf<UGameplayEffect>& effect : StartupGameplayEffect)
	{
		if (!effect)
		{
			continue;
		}
		
		UGameplayEffect* effectCDO = effect.GetDefaultObject();
		
		InWarriorASCToGive->ApplyGameplayEffectToSelf(effectCDO, applyLevel, InWarriorASCToGive->MakeEffectContext());
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& abilitiesToGive,
	UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 applyLevel)
{
	if(abilitiesToGive.IsEmpty())
	{
		return;
	}

	for(const TSubclassOf<UWarriorGameplayAbility>& ability : abilitiesToGive)
	{
		if(!ability)
		{
			continue;
		}

		FGameplayAbilitySpec abilitySpec(ability);
		abilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
		abilitySpec.Level = applyLevel;
		
		InWarriorASCToGive->GiveAbility(abilitySpec);
	}
}
