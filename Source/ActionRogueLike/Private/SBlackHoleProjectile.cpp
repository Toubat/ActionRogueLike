// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"

#include "PhysicsEngine/RadialForceComponent.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	Gravity = CreateDefaultSubobject<URadialForceComponent>(TEXT("Gravity"));
	Gravity->SetupAttachment(RootComponent);
	Gravity->Radius = 1000.f;
	Gravity->bImpulseVelChange = true;
	Gravity->bAutoActivate = false;
	Gravity->bIgnoreOwningActor = true;
}

void ASBlackHoleProjectile::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnSphereHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ASBlackHoleProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bBFromSweep, SweepResult);
}
