// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SBlackHoleProjectile.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASBlackHoleProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:

	ASBlackHoleProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	URadialForceComponent* Gravity;

	virtual void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult) override;
	
private:

};
