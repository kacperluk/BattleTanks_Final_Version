// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Engine/Classes/Engine/EngineTypes.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	ImpactBlast1 = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast1->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovment = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment"));
	ProjectileMovment->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>("Explosion Force");
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed) {

	ProjectileMovment->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovment->Activate();

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Your sadasdasde2134message"));
	ImpactBlast1->ActivateSystem(true);
}