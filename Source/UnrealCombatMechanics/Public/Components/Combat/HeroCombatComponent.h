// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;
/**
 * 
 */
UCLASS()
class UNREALCOMBATMECHANICS_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Warriot | Combat")
	AWarriorHeroWeapon* GetWarriorHeroWeaponByTag(FGameplayTag weaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category="Warriot | Combat")
	AWarriorHeroWeapon* GetHeroCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category="Warriot | Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float level) const;

	virtual void OnHitTargetActor(AActor* hitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* interactedActor) override;
};
