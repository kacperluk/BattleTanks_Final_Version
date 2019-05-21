// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAiminngComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};
class AProjectile;
class UTankBarrel;
class UTankTurret;
// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAiminngComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAiminngComponent();
	
	UFUNCTION(BlueprintCallable)
		void Fire();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet ,UTankTurret* TurretToSet);

protected:
	// Called when the game starts
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	EFiringStatus GetFiringState() const;
	UFUNCTION(BlueprintCallable)
		int32 getAmmoCount() const;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
private:
	void MoveBarrel(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = Firing)
		float ReloadTimeInSeconds = 3;
	
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000;
	UPROPERTY(EditAnywhere, Category = Firing)
		int32 Ammo = 15;
	bool IsBarrelMoving();
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection = FVector(0);
	double LastFireTime = 0;
};
