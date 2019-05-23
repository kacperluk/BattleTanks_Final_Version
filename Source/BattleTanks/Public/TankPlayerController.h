// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be last include

class ATank;
class UTankAiminngComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATankPlayerController();
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank *GetControlledTank() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAiminngComponent* AimingCompRef);
private:
	// Called when tank is being possesed
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnTankDeath();

	// Returns an OUT parameter , true if hit landscape
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	
	// Aims Towards crosshair
	void AimTowardsCroshair();

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
	
};
