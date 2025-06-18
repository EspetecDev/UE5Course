

#include "UCExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"


AUCExplosiveBarrel::AUCExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUCExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StaticMesh))
	{
		StaticMesh->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnComponentHit);
	}
}

void AUCExplosiveBarrel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	if (IsValid(StaticMesh))
	{
		StaticMesh->OnComponentBeginOverlap.RemoveAll(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

void AUCExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, ThisClass::Super* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(RadialForce))
	{
		RadialForce->FireImpulse();
	}
}