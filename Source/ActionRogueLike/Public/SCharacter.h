// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SProjectileBase.h"
#include "SCharacter.generated.h"

class USAttributeComponent;
class USInteractionComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASProjectileBase> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASProjectileBase> TeleportProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASProjectileBase> BlackHoleProjectileClass;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USAttributeComponent* AttributeComponent;
	
	virtual void BeginPlay() override;

	void Look(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void SpawnProjectile();
	
	void PrimaryAttack(const FInputActionValue& Value);

	void PrimaryInteract(const FInputActionValue& Value);

	void BlackHole(const FInputActionValue& Value);

	void Teleport(const FInputActionValue& Value);

	FVector GetCrossHairLocation() const;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

private:
	UPROPERTY(EditAnywhere)
	float FireRange = 5000.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASProjectileBase> CurrentProjectileClass;
	
	/* <EnhancedInput> */
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PrimaryAttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PrimaryInteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* BlackHoleAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* TeleportAction;
	/* </EnhancedInput> */

	/* <Animation Montages> */
	UPROPERTY(EditAnywhere, Category = Montages)
	UAnimMontage* PrimaryAttackMontage;
	/* </Animation Montages> */

	/* <TimerHandle> */
	FTimerHandle AttackTimer;
	/* </TimerHandle> */
};
