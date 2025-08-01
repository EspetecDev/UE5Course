

#include "UCMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UECourse/UCCharacter.h"
#include "UECourse/Components/UCAttributeComponent.h"


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

	SphereComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlap);
	SphereComp->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnHit);
}

void AUCMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	constexpr bool bShouldIgnore = true;
	SphereComp->IgnoreActorWhenMoving(GetOwner(), bShouldIgnore);
}

void AUCMagicProjectile::BeginDestroy()
{
	SphereComp->OnComponentBeginOverlap.RemoveAll(this);
	SphereComp->OnComponentHit.RemoveAll(this);
	Super::BeginDestroy();
}

void AUCMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(HitVFX))
		return;
	
	UGameplayStatics::SpawnEmitterAtLocation(this, HitVFX, GetActorLocation(), GetActorRotation());

	if (OtherActor && OtherActor->IsA(AUCCharacter::StaticClass()))
	{
		UUCAttributeComponent* AttributeComp = Cast<UUCAttributeComponent>(OtherActor->GetComponentByClass(UUCAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.f);
		}
	}
	
	Destroy();
}

void AUCMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, ThisClass::Super* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsValid(HitVFX))
		return;
	
	UGameplayStatics::SpawnEmitterAtLocation(this, HitVFX, GetActorLocation(), GetActorRotation());
	
	Destroy();
}
