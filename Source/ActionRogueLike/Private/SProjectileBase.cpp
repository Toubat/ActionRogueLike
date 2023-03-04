// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName("Projectile");
	Sphere->SetGenerateOverlapEvents(true);
	SetRootComponent(Sphere);

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect")); 
	Effect->SetupAttachment(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASProjectileBase::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void ASProjectileBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

