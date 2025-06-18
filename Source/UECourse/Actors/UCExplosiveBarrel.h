// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class UECOURSE_API AUCExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	AUCExplosiveBarrel();
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URadialForceComponent> RadialForce = nullptr;

protected:
	virtual void BeginPlay() override;

};
