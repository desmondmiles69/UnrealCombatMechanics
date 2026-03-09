// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
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
};
