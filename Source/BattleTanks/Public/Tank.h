// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;	// forward declarations
class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTank);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATank();
	// Called by the engine when actor is damaged
	virtual float TakeDamage(float DamageAmount,
							struct FDamageEvent const & DamageEvent,
							class AController * EventInstigator,
							AActor * DamageCauser
							)override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	FTank OnTankDeath;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	//initialized in BeginPlay
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;	
};
