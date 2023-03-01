// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	constexpr float Radius = 30.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	TArray<FHitResult> Hits;
	const bool bBlockingHits = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EyeLocation + EyeRotation.Vector() * 1000, FQuat::Identity, ObjectQueryParams, Shape);
	const FColor DebugColor = bBlockingHits ? FColor::Green : FColor::Red;

	for (const FHitResult& Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);
				ISGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 16, DebugColor, false, 2.f, 0, 2.f);
	}

	// Debug
	DrawDebugDirectionalArrow(GetWorld(), EyeLocation, EyeLocation + (EyeRotation.Vector() * 1000), 10.f, DebugColor, false, 2.f, 0, 2.f);
}