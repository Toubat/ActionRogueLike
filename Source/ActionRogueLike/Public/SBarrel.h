// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBarrel.generated.h"

class URadialForceComponent;
UCLASS()
class ACTIONROGUELIKE_API ASBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBarrel();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialForce;
	
	virtual void BeginPlay() override;

private:

};
