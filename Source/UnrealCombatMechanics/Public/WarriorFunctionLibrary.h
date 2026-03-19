// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "WarriorFunctionLibrary.generated.h"

class UWarriorAbilitySystemComponent;

UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes,
	No
};
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
};
