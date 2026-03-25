// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealCombatMechanics/Public/Characters/WarriorHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/WarriorInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorGameplayTags.h"
#include "AbilitiesSystem/WarriorAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/Combat/HeroCombatComponent.h"

#include "UnrealCombatMechanics/Public/WarriorDebugHelper.h"

AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Input Config data asset is missing"));
	ULocalPlayer* localPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* subSystem =  ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);

	check(subSystem);
	subSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UWarriorInputComponent* inputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);

	inputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AWarriorHeroCharacter::Input_Move);
	inputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AWarriorHeroCharacter::Input_Look);

	inputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(WarriorAbilitySystemComponent && WarriorAttributeSet)
	{
		if(!CharacterStartupData.IsNull())
		{
			if(UDataAsset_StartUpDataBase* loadedAbilityData = CharacterStartupData.LoadSynchronous())
			{
				loadedAbilityData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
			}
		}
	}
}

UPawnCombatComponent* AWarriorHeroCharacter::GetPawnCombatComponent()
{
	return HeroCombatComponent;
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& value)
{
	FVector2D moveInputValue = value.Get<FVector2D>();
	const FRotator movementRotation(0.f, GetController()->GetControlRotation().Yaw, 0.f);
	if(moveInputValue.Y != 0)
	{
		const FVector forwardDirection = movementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(forwardDirection, moveInputValue.Y);
	}

	if(moveInputValue.X != 0)
	{
		const FVector rightDirection = movementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(rightDirection, moveInputValue.X);
	}
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& value)
{
	const FVector2D lookInputValue = value.Get<FVector2D>();

	if(lookInputValue.X != 0)
	{
		AddControllerYawInput(lookInputValue.X);
	}
	if(lookInputValue.Y != 0)
	{
		AddControllerPitchInput(lookInputValue.Y);
	}
}

void AWarriorHeroCharacter::AbilityInputPressed(FGameplayTag abilityInputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputPressed(abilityInputTag);
}

void AWarriorHeroCharacter::AbilityInputReleased(FGameplayTag abilityInputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputReleased(abilityInputTag);
}
