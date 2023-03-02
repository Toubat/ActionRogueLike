// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASItemChest::ASItemChest(): TargetPitch(110)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(GetRootComponent());

	GoldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoldMesh"));
	GoldMesh->SetupAttachment(GetRootComponent());

	TreasureParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TreasureParticles"));
	TreasureParticles->SetAutoActivate(false);
	TreasureParticles->SetupAttachment(GoldMesh);
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

