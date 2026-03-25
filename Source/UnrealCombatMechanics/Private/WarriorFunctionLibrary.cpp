// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorFunctionLibrary.h"

#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interfaces/PawnCombatInterface.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* actor)
{
	check(actor);
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(actor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* actor, FGameplayTag tagToAdd)
{
	UWarriorAbilitySystemComponent* abilitySystemComponent = NativeGetWarriorASCFromActor(actor);
	if(!abilitySystemComponent->HasMatchingGameplayTag(tagToAdd))
	{
		abilitySystemComponent->AddLooseGameplayTag(tagToAdd);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* actor, FGameplayTag tagToRemove)
{
	UWarriorAbilitySystemComponent* abilitySystemComponent = NativeGetWarriorASCFromActor(actor);
	if(abilitySystemComponent->HasMatchingGameplayTag(tagToRemove))
	{
		abilitySystemComponent->RemoveLooseGameplayTag(tagToRemove);
	}
}

bool UWarriorFunctionLibrary::NativeDoesActorHasTag(AActor* actor, FGameplayTag tagToCheck)
{
	UWarriorAbilitySystemComponent* abilitySystem = NativeGetWarriorASCFromActor(actor);
	return abilitySystem->HasMatchingGameplayTag(tagToCheck);
}

void UWarriorFunctionLibrary::BP_DoesActorHasGameplayTag(AActor* actor, FGameplayTag tagToCheck, EWarriorConfirmType& outWarriorConfirmType)
{
	outWarriorConfirmType = NativeDoesActorHasTag(actor, tagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponent(AActor* actor)
{
	if(IPawnCombatInterface* combatInterface = Cast<IPawnCombatInterface>(actor))
	{
		return combatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponent(AActor* actor, EWarriorValidType& outWarriorValidType)
{
	UPawnCombatComponent* combatComponent = NativeGetPawnCombatComponent(actor);
	outWarriorValidType = combatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;
	return combatComponent;
}
