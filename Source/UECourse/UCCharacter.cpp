// Fill out your copyright notice in the Description page of Project Settings.


#include "UCCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AUCCharacter::AUCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AUCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUCCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AUCCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
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
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);

}

