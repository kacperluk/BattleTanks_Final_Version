// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "TankAiminngComponent.h"
#include "Tank.h"

#include "Engine/World.h"




ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank> ( GetPawn() );
}

// Sets default values
ATankPlayerController::ATankPlayerController()
{
}


// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAiminngComponent>();
	if (ensure(AimingComponent)) {

		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bSpectatorModeActive == false)
		AimTowardsCroshair();
}

void ATankPlayerController::AimTowardsCroshair()
{
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAiminngComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;	// Out parameter
	bool bHaveAimingSolution = GetSightRayHitLocation(HitLocation);
	if (bHaveAimingSolution)
	{
		AimingComponent->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// find the crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	// "De-Prosject" the screen position of the crosshair to the world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		
		// line trace along that direction and see what we hit (up to man range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation , FVector& LookDirection) const{
	FVector CameraWorldLocation;		// To be discarded
	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}
void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if(InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		// Subscribe our local method to the tanks death event
		PossesedTank->OnTankDeath.AddUniqueDynamic(this,&ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("You Died"), *this->GetName());
	
	bSpectatorModeActive = true;
	this->StartSpectatingOnly();
}