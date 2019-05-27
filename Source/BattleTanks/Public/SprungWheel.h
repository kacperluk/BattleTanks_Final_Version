// Copyright BadGamesButCheap

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
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

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Mass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Wheel = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

};
