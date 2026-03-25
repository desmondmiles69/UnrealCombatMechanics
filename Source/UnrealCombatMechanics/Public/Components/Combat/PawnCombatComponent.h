// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

/**
 * 
 */
class AWarriorWeaponBase;
UCLASS()
class UNREALCOMBATMECHANICS_API UPawnCombatComponent : public UPawnExtensionComponentBase
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

	UFUNCTION(BlueprintCallable, Category = "Warrior | Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType toggleDamageType);

	virtual void OnHitTargetActor(AActor* hitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* interactedActor);

protected:
	TArray<AActor*> OverlappedActors;
private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};
