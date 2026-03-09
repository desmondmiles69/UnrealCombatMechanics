// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

/**
 * 
 */
class AWarriorWeaponBase;
UCLASS()
class COMBATCOURSE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior | Combat")
	void RegisterSpawnedWeapon(FGameplayTag weaponTagToRegister, AWarriorWeaponBase* weaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category= "Warrior | Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag weaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Warriot | Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable)
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;
private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};
