// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetWarriorHeroWeaponByTag(FGameplayTag weaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(weaponTag));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float level) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(level);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* hitActor)
{
	if(OverlappedActors.Contains(hitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(hitActor);

	FGameplayEventData weaponHitData;
	weaponHitData.Instigator = GetOwningPawn();
	weaponHitData.Target = hitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Shared_Event_MeeleHit, weaponHitData);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* interactedActor)
{
	  
}
