// Fill out your copyright notice in the Description page of Project Settings.

#include "TanksTrack.h"
#include "Engine/World.h"
#include "SpawnPoint.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
UTanksTrack::UTanksTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);
}

void UTanksTrack::SetThrottle(float Throttle) 
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}
void UTanksTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied =  CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();

	float ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel: Wheels) 
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTanksTrack::GetWheels() const
{/*
	TArray<USceneComponent*> SpawnPoints;
	TArray<USceneComponent*> SprungWheels;
	TArray<ASprungWheel*> ConvertedSprungWheels;
	GetChildrenComponents(false, SpawnPoints);
	for(auto CurrentSpawnPoint : SpawnPoints)
	{
		TArray<USceneComponent*> ChildrenOfCurrentSP;
		CurrentSpawnPoint->GetChildrenComponents(false, ChildrenOfCurrentSP);
		SprungWheels.Append(ChildrenOfCurrentSP);
	}
	for(auto CurrentSprungWheel : SprungWheels)
	{
		ConvertedSprungWheels.Append(Cast<ASprungWheel*>(CurrentSprungWheel),1);
	}
	return ConvertedSprungWheels;*/
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*>Children;
	GetChildrenComponents(true, Children);
	for(auto Child:Children)
	{
		USpawnPoint* SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActors();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}

void UTanksTrack::BeginPlay() {
	Super::BeginPlay();
}
