

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
}

// Called every frame
void AUCExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

