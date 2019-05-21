// Fill out your copyright notice in the Description page of Project Settings.

#include "TanksTrack.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
UTanksTrack::UTanksTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);
}

void UTanksTrack::ApplySidewaysForce()
{
	auto SlippagSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto Forceslippage = GetRightVector() * SlippagSpeed;

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippagSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// Divided by 2 because tank has 2 tracks 
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAcceleration / 2;
	TankRoot->AddForce(CorrectionForce);
}
void UTanksTrack::SetThrottle(float Throttle) 
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}
void UTanksTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTanksTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTanksTrack::OnHit);
}
void UTanksTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}
