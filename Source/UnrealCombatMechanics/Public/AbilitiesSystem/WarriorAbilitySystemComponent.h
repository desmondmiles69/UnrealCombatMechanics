// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOMBATMECHANICS_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& inputTag);
	void OnAbilityInputReleased(const FGameplayTag& inputTag);

	UFUNCTION(BlueprintCallable, Category="Warrior | Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& defaultWeaponAbilitySet, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& grantedWeaponAbilities);

	UFUNCTION(BlueprintCallable, Category = "Warriot | Ability")
	void RemoveGrantedAbilitySpecHandles(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& specHandlesToRemove);
};
