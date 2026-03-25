// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarriorWeaponBase.h"

#include "WarriorDebugHelper.h"
#include "Components/BoxComponent.h"

// Sets default values
AWarriorWeaponBase::AWarriorWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentEndOverlap);
}

void AWarriorWeaponBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* weaponOwningPawn = GetInstigator<APawn>();
	checkf(weaponOwningPawn, TEXT("Forgot to assign a valid instigator as the owning pawn of the weapon %s"), *GetName());

	if(APawn* hitPawn = Cast<APawn>(OtherActor))
	{
		if(weaponOwningPawn != hitPawn)
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
		//TODO: Implement hit for enemy characters
	}
}

void AWarriorWeaponBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* weaponOwningPawn = GetInstigator<APawn>();
	checkf(weaponOwningPawn, TEXT("Forgot to assign a valid instigator as the owning pawn of the weapon %s"), *GetName());

	if(APawn* hitPawn = Cast<APawn>(OtherActor))
	{
		if(weaponOwningPawn != hitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
		//TODO: Implement hit for enemy characters
	}
}

