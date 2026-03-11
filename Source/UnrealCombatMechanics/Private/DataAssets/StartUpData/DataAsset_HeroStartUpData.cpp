// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "AbilitiesSystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 applyLevel)
{
	Super::GiveToAbilitySystemComponent(InWarriorASCToGive, applyLevel);

	for(const FWarriorHeroAbilitySet& abilitySet: HeroStartupAbilitySets)
	{
		if(!abilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec abilitySpec(abilitySet.AbilityToGrant);
		abilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
		abilitySpec.Level = applyLevel;
		abilitySpec.GetDynamicSpecSourceTags().AddTag(abilitySet.InputTag);
		
		InWarriorASCToGive->GiveAbility(abilitySpec);
	}
}
