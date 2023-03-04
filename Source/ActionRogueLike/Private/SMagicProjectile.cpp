// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	Sphere->IgnoreActorWhenMoving(GetInstigator(), true);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnSphereBeginOverlap);
	Sphere->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnSphereHit);
}

void ASMagicProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 100.f, 12, FColor::Red);
}

void ASMagicProjectile::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetInstigator()) return;
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, GetActorLocation(), GetActorRotation());
	Destroy();
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

