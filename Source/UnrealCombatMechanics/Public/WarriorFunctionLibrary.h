// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "WarriorTypes/WarriorEnumTypes.h"
#include "WarriorFunctionLibrary.generated.h"

class UPawnCombatComponent;
class UWarriorAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class UNREALCOMBATMECHANICS_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Warrior | FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* actor, FGameplayTag tagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Warrior | FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* actor, FGameplayTag tagToRemove);

	static bool NativeDoesActorHasTag(AActor* actor, FGameplayTag tagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Warrior | FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "outWarriorConfirmType"))
	static void BP_DoesActorHasGameplayTag(AActor* actor, FGameplayTag tagToCheck, EWarriorConfirmType& outWarriorConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponent(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Warrior | FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component", ExpandEnumAsExecs = "outWarriorValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponent(AActor* actor, EWarriorValidType& outWarriorValidType);
};
