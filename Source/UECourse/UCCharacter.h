// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UCCharacter.generated.h"

class UUCInteractComponent;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TObjectPtr<UUCInteractComponent> InteractComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<AActor> ProjectileClass = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<AActor> UltimateProjectileClass = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<AActor> TeleportProjectileClass = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackAnim = nullptr;

	FTimerHandle AttackTimerHandle;
	FTimerHandle TeleportStartTimerHandle;

protected:
	virtual void BeginPlay() override;

	// Input
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void PrimaryAttack();
	void UltimateAttack();
	void LaunchInteract();
	void Teleport();

	// Timers
	void AttackTimerEnd();
	void TeleportTimerEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void FakeAttack();

public:	

	AUCCharacter();
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
