// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class UNREALCOMBATMECHANICS_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()
	void NativeInitializeAnimation() override;
	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData | References")
	AWarriorHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData | LocomotionData")
	float IdleElapsedTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData | LocomotionData")
	float EnterRelaxThresholdTime;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData | LocomotionData")
	bool bCanRelax;
};
