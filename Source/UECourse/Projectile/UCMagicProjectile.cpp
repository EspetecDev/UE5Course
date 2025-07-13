

#include "UCMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AUCMagicProjectile::AUCMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	// Way 1 - Custom checks
	// SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	// SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	// Way 2 - Create custom preset and assign it
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void AUCMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnHit);
}

void AUCMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	constexpr bool bShouldIgnore = true;
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), bShouldIgnore);
}

void AUCMagicProjectile::BeginDestroy()
{
	SphereComp->OnComponentBeginOverlap.RemoveAll(this);
	Super::BeginDestroy();
}

void AUCMagicProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, ThisClass::Super* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(HitVFX))
		return;
	
	UGameplayStatics::SpawnEmitterAtLocation(this, HitVFX, GetActorLocation(), GetActorRotation());
	Destroy();
}
