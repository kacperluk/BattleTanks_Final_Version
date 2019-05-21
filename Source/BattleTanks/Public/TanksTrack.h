// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TanksTrack.generated.h"

// TanksTrack is used to set maximum driving force, and to apply forces to tank
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTanksTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable , Category = Input)
		void SetThrottle(float Throttle);

	void DriveTrack();

	UTanksTrack();
	// Max force per track, in Newtons
	UPROPERTY(EditAnywhere, Category = Physics)
		float TrackMaxDrivingForce = 35000000; // Assume 40 tonne tank, and 1g accelleration
protected:

	void ApplySidewaysForce();
	
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
					UPrimitiveComponent* OtherComponent, FVector NormalImpulse ,
					const FHitResult& Hit);

	float CurrentThrottle = 0;

};
