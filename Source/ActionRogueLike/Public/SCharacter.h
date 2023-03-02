// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

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
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent;

	virtual void BeginPlay() override;

	void Look(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void SpawnProjectile();
	void PrimaryAttack(const FInputActionValue& Value);

	void PrimaryInteract(const FInputActionValue& Value);

private:
	
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
	/* </EnhancedInput> */

	/* <Animation Montages> */
	UPROPERTY(EditAnywhere, Category = Montages)
	UAnimMontage* PrimaryAttackMontage;
	/* </Animation Montages> */

	/* <TimerHandle> */
	FTimerHandle PrimaryAttackTimer;
	/* </TimerHandle> */
};
