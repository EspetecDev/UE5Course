// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCMagicProjectile.h"
#include "AUCTeleportProjectile.generated.h"

UCLASS()
class UECOURSE_API AAUCTeleportProjectile : public AUCMagicProjectile
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Config)
	TObjectPtr<UParticleSystem> DestroyVFX = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Config)
	float WaitToExplodeTime = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Config)
	float WaitToTeleportTime = 0.2f;

private:

	FTimerHandle TimerHandle;

public:
	AAUCTeleportProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

	void OnExplodeTimerEnds();
	void OnTimerComplete();

};
