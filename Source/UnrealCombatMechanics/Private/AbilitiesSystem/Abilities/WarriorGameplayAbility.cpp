// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitiesSystem/Abilities/WarriorGameplayAbility.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if(AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponetFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponetFromActorInfo() const
{
	return Cast<UWarriorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UWarriorGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& specHandle)
{
	UAbilitySystemComponent* targetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);
	
	check(targetAsc && specHandle.IsValid())
	
	return GetWarriorAbilitySystemComponetFromActorInfo()->ApplyGameplayEffectSpecToTarget(*specHandle.Data, targetAsc);
}

FActiveGameplayEffectHandle UWarriorGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& specHandle, EWarriorSuccessType& outSuccessType)
{
	FActiveGameplayEffectHandle gameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(targetActor, specHandle);
	
	outSuccessType = gameplayEffectHandle.WasSuccessfullyApplied() ? EWarriorSuccessType::Successful : EWarriorSuccessType::Failed;
	return gameplayEffectHandle;
}
