// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20; // Sensible dafault

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesElevation = 50;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinDegreesElevation = 0;
	
};
