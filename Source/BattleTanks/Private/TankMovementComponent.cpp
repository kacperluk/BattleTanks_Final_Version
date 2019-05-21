// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TanksTrack.h"
 
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	// No need to call Super as we're replacing the funcionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	auto Throw = FVector::DotProduct(TankForward, AIForwardIntention);
	
	auto RightThrow = FVector::CrossProduct( AIForwardIntention,TankForward).Z;

	IntendTurnRight(RightThrow);
    IntendMoveForward(Throw);
}
void UTankMovementComponent::Initialise(UTanksTrack* LeftTrackToSet, UTanksTrack* RightTrackToSet) 
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

