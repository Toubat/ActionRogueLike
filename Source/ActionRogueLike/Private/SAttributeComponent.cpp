// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = 100.f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}
