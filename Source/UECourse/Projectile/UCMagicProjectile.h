#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UCMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class UECOURSE_API AUCMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AUCMagicProjectile();
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComp = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> MovementComp = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystemComponent> ParticleComp = nullptr;
	
protected:

	virtual void BeginPlay() override;



	
	
};
