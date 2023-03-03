// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputContext, 0);
		}
	}
	
}

void ASCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Look = Value.Get<FVector2D>();

	AddControllerYawInput(Look.X);
	AddControllerPitchInput(Look.Y);
}

void ASCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>();
	
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
	const FVector ControlForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector ControlRightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// FVector Start = GetActorLocation();
	// Start.Z += 50.f;
	// DrawDebugDirectionalArrow(GetWorld(), Start, Start + GetActorForwardVector() * 200.f, 100.f, FColor::Red);
	// DrawDebugDirectionalArrow(GetWorld(), Start, Start + ControlForwardDirection * 200.f, 100.f, FColor::Green);

	AddMovementInput(ControlForwardDirection, Movement.X);
	AddMovementInput(ControlRightDirection, Movement.Y);
}

void ASCharacter::Jump(const FInputActionValue& Value)
{
	Super::Jump();

	UE_LOG(LogTemp, Warning, TEXT("Jump"));
}

void ASCharacter::SpawnProjectile() 
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	const FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, GetCrossHairLocation());
	
	const FTransform ProjectileTransform(LookRotation, HandLocation);
	
	FActorSpawnParameters ProjectileParams;
	ProjectileParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ProjectileParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileTransform, ProjectileParams);
}

void ASCharacter::PrimaryAttack(const FInputActionValue& Value) 
{
	PlayAnimMontage(PrimaryAttackMontage);
	GetWorldTimerManager().SetTimer(PrimaryAttackTimer, this, &ASCharacter::SpawnProjectile, 0.2f);
}

void ASCharacter::PrimaryInteract(const FInputActionValue& Value)
{
	InteractionComponent->PrimaryInteract();
}

FVector ASCharacter::GetCrossHairLocation() const
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector Rotation = Camera->GetComponentRotation().Vector();
	const FVector End = Start + Rotation * FireRange;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	
	FHitResult Hit;
	bool bBlockHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	if (bBlockHit) {
		// DrawDebugSphere(GetWorld(), Start, 100.f, 16, FColor::Red);
		// DrawDebugLine(GetWorld(), Start, End, FColor::Green);
		// DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 100.f, 16, FColor::Blue);
		// DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 5.f, FColor::Blue);
	}
	
	return bBlockHit ? Hit.Location : End;
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCharacter::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASCharacter::Jump);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryInteract);
	}
}

