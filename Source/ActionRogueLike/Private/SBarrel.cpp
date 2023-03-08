// Fill out your copyright notice in the Description page of Project Settings.


#include "SBarrel.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"
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
	RadialForce->SetAutoActivate(false);
	RadialForce->ImpulseStrength = 2000.f;
	RadialForce->Radius = 600.f;
	RadialForce->bImpulseVelChange = true;
	RadialForce->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ASBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ASBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Mesh->OnComponentHit.AddUniqueDynamic(this, &ASBarrel::OnMeshHit);
}

void ASBarrel::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OnMeshHit"));
	RadialForce->FireImpulse();

	USAttributeComponent* Attribute = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (Attribute)
	{
		Attribute->ApplyHealthChange(-50.f);
		Destroy();
	}
}

// Called every frame
void ASBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

