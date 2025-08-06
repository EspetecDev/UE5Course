// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCTargetDummy.generated.h"

class UUCAttributeComponent;

UCLASS()
class UECOURSE_API AUCTargetDummy : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUCAttributeComponent> AttributeComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent = nullptr;

public:
	AUCTargetDummy();

protected:

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnHealthChanged(AActor* ActorInstigator, UUCAttributeComponent* OwningComp, float NewHealth, float Delta);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
