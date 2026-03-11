// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarriorHeroWeapon.h"

void AWarriorHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& specHandles)
{
	GrantedWeaponAbilitiesSpecHandles = specHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarriorHeroWeapon::GetGrantedWeaponAbilitiesSpecHandles() const
{
	return GrantedWeaponAbilitiesSpecHandles;
}
