// Fill out your copyright notice in the Description page of Project Settings.


#include "SBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASBarrel::ASBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	SetRootComponent(Mesh);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->ImpulseStrength = 20000.f;
	RadialForce->Radius = 600.f;
	RadialForce->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ASBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

