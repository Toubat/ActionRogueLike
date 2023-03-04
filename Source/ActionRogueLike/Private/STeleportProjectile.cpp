// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTeleportProjectile::ASTeleportProjectile()
{
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(OpenPortalTimer, this, &ASTeleportProjectile::SpawnTeleportPortal, OpenPortalDuration);
}

void ASTeleportProjectile::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnSphereHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	GetWorldTimerManager().ClearTimer(OpenPortalTimer);
	SpawnTeleportPortal();
}

void ASTeleportProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bBFromSweep, SweepResult);
}

void ASTeleportProjectile::SpawnTeleportPortal()
{
	ProjectileMovement->StopMovementImmediately();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, GetActorLocation(), GetActorRotation());
	GetWorldTimerManager().SetTimer(TeleportTimer, this, &ASTeleportProjectile::TeleportInstigator, TeleportDuration);
}

void ASTeleportProjectile::TeleportInstigator()
{
	if (GetInstigator()) GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();
}
