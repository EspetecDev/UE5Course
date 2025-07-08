// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCMagicProjectile.h"
#include "AUCTeleportProjectile.generated.h"

UCLASS()
class UECOURSE_API AAUCTeleportProjectile : public AUCMagicProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAUCTeleportProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
