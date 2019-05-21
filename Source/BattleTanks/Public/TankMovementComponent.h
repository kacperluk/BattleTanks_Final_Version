// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTanksTrack;
/**
 * Responsible for driving the tank tracks
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	// used to assagin track pointers 
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTanksTrack* LeftTrackToSet, UTanksTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throw);

private:
	// Called from the pathfinding logic by AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTanksTrack* LeftTrack = nullptr;
	UTanksTrack* RightTrack = nullptr;
};
