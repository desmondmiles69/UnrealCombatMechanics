// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarriorGameplayAbility;
class UWarriorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class UNREALCOMBATMECHANICS_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 applyLevel = 1);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& abilitiesToGive, UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 applyLevel = 1);
};
