// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag weaponTagToRegister, AWarriorWeaponBase* weaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(weaponTagToRegister), TEXT("Weapon %s is already registered as a carried weapon"), *weaponTagToRegister.ToString());
	check(weaponToRegister);

	CharacterCarriedWeaponMap.Emplace(weaponTagToRegister, weaponToRegister);

	weaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	weaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
	if(bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = weaponTagToRegister;
	}

	const FString msg = FString::Printf(TEXT("A weapon %s has been register with tag %s"), *weaponToRegister->GetName(), *weaponTagToRegister.ToString());
	Debug::Print(msg);
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag weaponTagToGet) const
{
	if(CharacterCarriedWeaponMap.Contains(weaponTagToGet))
	{
	 	if(AWarriorWeaponBase* const* foundWeapon = CharacterCarriedWeaponMap.Find(weaponTagToGet))
	 	{
	 		return *foundWeapon;
	 	}
	}
	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType toggleDamageType)
{
	if(toggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWarriorWeaponBase* currentWeapon = GetCharacterCurrentEquippedWeapon();
		check(currentWeapon);
		if(bShouldEnable)
		{
			currentWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		}
		else
		{
			currentWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* hitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* interactedActor)
{
}
