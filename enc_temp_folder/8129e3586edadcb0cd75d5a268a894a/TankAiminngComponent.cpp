// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAiminngComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"

#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"



// Sets default values for this component's properties
UTankAiminngComponent::UTankAiminngComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAiminngComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { 
		
		return; }
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
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = this->GetOwner()->GetName();
		MoveBarrel(AimDirection);
		
	}
	
}

void UTankAiminngComponent::MoveBarrel(FVector AimDirection) 
{
	// Work-out difference between barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

// Called when the game starts
void UTankAiminngComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAiminngComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ... 
}

void UTankAiminngComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) 
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}