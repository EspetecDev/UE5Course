#include "UCTargetDummy.h"

#include "UECourse/Components/UCAttributeComponent.h"


AUCTargetDummy::AUCTargetDummy()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	AttributeComponent = CreateDefaultSubobject<UUCAttributeComponent>("AttributeComponent");
	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);
}

void AUCTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComponent->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnHit);
}

void AUCTargetDummy::OnHealthChanged(AActor* ActorInstigator, UUCAttributeComponent* OwningComp, float NewHealth,
                                     float Delta)
{
	if (NewHealth >= 0.f && Delta < 0.f)
	{
		MeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
	}
}

void AUCTargetDummy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AttributeComponent->ApplyHealthChange(-10.f);
}
