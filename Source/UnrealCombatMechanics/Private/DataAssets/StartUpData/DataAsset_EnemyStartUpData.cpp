// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "AbilitiesSystem/Abilities/WarriorEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 applyLevel)
{
	Super::GiveToAbilitySystemComponent(InWarriorASCToGive, applyLevel);
	
	for (const TSubclassOf<UWarriorEnemyGameplayAbility>& ability : EnemyStartupAbilities)
	{
		if (!ability) continue;
		
		FGameplayAbilitySpec abilitySpec(ability);
		abilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
		abilitySpec.Level = applyLevel;
		
		InWarriorASCToGive->GiveAbility(abilitySpec);
	}
}
