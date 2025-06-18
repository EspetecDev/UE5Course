// Fill out your copyright notice in the Description page of Project Settings.


#include "UCCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AUCCharacter::AUCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AUCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUCCharacter::MoveForward(float Value)
{
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.f;
	ControlRotator.Roll = 0.f;
	AddMovementInput(ControlRotator.Vector(), Value);
}

void AUCCharacter::MoveRight(float Value)
{
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.f;
	ControlRotator.Roll = 0.f;
	FVector RightRotatorVector = UKismetMathLibrary::GetRightVector(ControlRotator);
	AddMovementInput(RightRotatorVector, Value);
}

void AUCCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AUCCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AUCCharacter::PrimaryAttack()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetActorRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}

void AUCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	
	// PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	// PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &ThisClass::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

}

