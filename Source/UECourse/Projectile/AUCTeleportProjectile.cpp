#include "AUCTeleportProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

AAUCTeleportProjectile::AAUCTeleportProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAUCTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::OnTimerComplete, WaitToTeleportTime);
}

void AAUCTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAUCTeleportProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	OnTimerComplete();
}

void AAUCTeleportProjectile::OnTimerComplete()
{
	if (!IsValid(DestroyVFX))
		return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyVFX, GetActorLocation(),GetActorRotation());
	MovementComp->StopMovementImmediately();
	
	FTimerHandle ExplodeTimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::OnExplodeTimerEnds, 0.2);
}

void AAUCTeleportProjectile::OnExplodeTimerEnds()
{
	AActor* InstigatorActor = GetInstigator();
	if (!IsValid(InstigatorActor))
		return;

	InstigatorActor->SetActorLocation(GetActorLocation());
	Destroy();
}



