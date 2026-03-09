// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningCharacterMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter || !OwningCharacterMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacterMovementComponent->Velocity.Size2D();
	bHasAcceleration = OwningCharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0;
}
