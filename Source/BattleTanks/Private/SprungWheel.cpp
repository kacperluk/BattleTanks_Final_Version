// Copyright BadGamesButCheap



#include "SprungWheel.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
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
	
	TotalForceMagnitudeThisFrame += ForceMgnitude;
	//UE_LOG(LogTemp, Warning, TEXT(" appling force %s"), *ForceToApply.ToString());
	//Wheel1->AddForce(Axle1->GetForwardVector() * ForceMgnitude);
	//Wheel1->AddForce()
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel1->SetNotifyRigidBodyCollision(true);
	Wheel1->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

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

	TotalForceMagnitudeThisFrame = 0.0f;
	//if(GetWorld()->TickGroup == TG_PostPhysics)

	//UE_LOG(LogTemp, Warning, TEXT("Tick %f"), GetWorld()->GetTimeSeconds());
	//ForceToApply.Set(0.0f, 0.0f, 0.0f);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
	//UE_LOG(LogTemp, Warning, TEXT("OnHit %f appling force %s"),GetWorld()->GetTimeSeconds(),*ForceToApply.ToString());
}

void ASprungWheel::ApplyForce()
{
	Wheel1->AddForce(Axle1->GetForwardVector() * TotalForceMagnitudeThisFrame);
	
}
