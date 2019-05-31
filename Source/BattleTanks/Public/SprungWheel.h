// Copyright BadGamesButCheap

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupConstraint();
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Axle1 = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Wheel1 = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

};
