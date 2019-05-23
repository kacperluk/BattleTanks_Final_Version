// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAiminngComponent;
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// How close can the AI tank get 
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 3000;
private:
	// Called when tank is being possesed
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnTankDeath();

	bool bControlledTankAlive = true;
};
