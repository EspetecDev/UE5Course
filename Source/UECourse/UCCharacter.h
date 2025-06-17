// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UCCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UECOURSE_API AUCCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void Turn(float Value);


public:	

	AUCCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
