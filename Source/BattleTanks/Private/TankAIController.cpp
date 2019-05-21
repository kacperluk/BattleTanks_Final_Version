// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "TankAiminngComponent.h"
#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = Cast<ATank>(GetPawn());

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAiminngComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	if(PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim towards player

		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		//If aiming or locked 

		auto FiringStatus = AimingComponent->GetFiringState();

		if(FiringStatus == EFiringStatus::Locked)
		AimingComponent->Fire(); // TODO Dont fire every frame like a retard
		return;
	}
}
