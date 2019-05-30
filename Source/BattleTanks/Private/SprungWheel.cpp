// Copyright BadGamesButCheap



#include "SprungWheel.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle1 = CreateDefaultSubobject<USphereComponent>(FName("Axle1"));
	Axle1->SetupAttachment(MassWheelConstraint);

	Wheel1 = CreateDefaultSubobject<USphereComponent>(FName("Wheel1"));
	Wheel1->SetupAttachment(Axle1);
	
	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle1);

}

void ASprungWheel::AddDrivingForce(float ForceMgnitude)
{
	Wheel1->AddForce(Axle1->GetForwardVector() * ForceMgnitude);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}
void ASprungWheel::SetupConstraint(){
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle1, NAME_None);

		AxleWheelConstraint->SetConstrainedComponents(Axle1, NAME_None, Wheel1, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

