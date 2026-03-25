// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitiesSystem/Abilities/WarriorHeroGameplayAbility.h"
#include "UnrealCombatMechanics/Public/Characters/WarriorHeroCharacter.h"
#include "UnrealCombatMechanics/Public/Controllers/WarriorHeroController.h"
#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if(!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponent()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> effectClass, float weaponBaseDamage, FGameplayTag currentAttackTypeTag, int32 currentComboCount)
{
	check(effectClass);
	
	FGameplayEffectContextHandle effectContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	effectContextHandle.SetAbility(this);
	effectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	effectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle effectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(effectClass, GetAbilityLevel(), effectContextHandle);
	
	effectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage, weaponBaseDamage);
	
	if (currentAttackTypeTag.IsValid())
	{
		effectSpecHandle.Data->SetSetByCallerMagnitude(currentAttackTypeTag, currentComboCount);
	}
	
	return effectSpecHandle;
}


