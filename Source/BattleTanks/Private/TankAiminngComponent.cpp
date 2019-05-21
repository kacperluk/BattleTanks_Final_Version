// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAiminngComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"



// Sets default values for this component's properties
UTankAiminngComponent::UTankAiminngComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

}

// Called every frame
void UTankAiminngComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}


void UTankAiminngComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity;

	// Calculate the Out launch veliocity
	auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	AimDirection = OutLaunchVelocity.GetSafeNormal();
	
	if (bHaveAimSolution)
	{
		//AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = this->GetOwner()->GetName();
		MoveBarrel(AimDirection);
	}
}

void UTankAiminngComponent::MoveBarrel(FVector AimDirection) 
{
	if (!ensure(Barrel)) { return; }
	// Work-out difference between barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	if (FMath::Abs(DeltaRotator.Yaw) < 180.0f)
		Turret->Rotate(DeltaRotator.Yaw);
	else
		Turret->Rotate(-DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

bool UTankAiminngComponent::IsBarrelMoving()
{
	auto CurrentDirection = Barrel->GetForwardVector();
	return !AimDirection.Equals(CurrentDirection, 0.01f);
}

// Called when the game starts
void UTankAiminngComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAiminngComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) 
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAiminngComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading && Ammo>0) {
		if (!ensure(Barrel) && !ensure(ProjectileBlueprint)) { return; }
		auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		// Spawn a projectile at the socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				SocketLocation,
				SocketRotation
				);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Ammo--;
	}
}

int32 UTankAiminngComponent::getAmmoCount() const{ return Ammo; }
EFiringStatus UTankAiminngComponent::GetFiringState() const
{
	return FiringStatus;
}

