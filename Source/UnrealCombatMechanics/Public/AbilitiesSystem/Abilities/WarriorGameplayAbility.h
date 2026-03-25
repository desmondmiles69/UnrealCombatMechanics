// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarriorTypes/WarriorEnumTypes.h"
#include "WarriorGameplayAbility.generated.h"

class UWarriorAbilitySystemComponent;
class UPawnCombatComponent;
/**
 * 
 */
UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8
{
	OnGiven,
	OnTriggered
};

UCLASS()
class UNREALCOMBATMECHANICS_API UWarriorGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:

	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface.
	
	UPROPERTY(EditDefaultsOnly, Category = "WarriorAbility")
	EWarriorAbilityActivationPolicy AbilityActivationPolicy = EWarriorAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "WarriorAbility")
	UPawnCombatComponent* GetPawnCombatComponetFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "WarriorAbility")
	UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponetFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& specHandle);
	
	UFUNCTION(BlueprintCallable, Category = "WarriorAbility", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "outSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& specHandle, EWarriorSuccessType& outSuccessType);
};
