#include "UCInteractComponent.h"

#include "UECourse/Interfaces/UCGameplayInterface.h"


UUCInteractComponent::UUCInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UUCInteractComponent::PrimaryInteract()
{
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	if (!IsValid(InstigatorPawn))
		return;
	
	FVector Start;
	FRotator StartRotation;
	InstigatorPawn->GetActorEyesViewPoint(Start, StartRotation);
	FVector End = Start + StartRotation.Vector() * 1000.f;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	// FHitResult Hit;
	// const bool bIsHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);
	// const FColor DebugLineColor = bIsHit ? FColor::Green : FColor::Red;
	// DrawDebugLine(GetWorld(), Start, End, DebugLineColor, false, 2.f, 0, 2.f);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	constexpr float SphereRadius = 30.f;
	Shape.SetSphere(SphereRadius);
	const bool bIsHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);
	const FColor DebugLineColor = bIsHit ? FColor::Green : FColor::Red;
	

	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (IsValid(HitActor))
		{
			if (HitActor->Implements<UUCGameplayInterface>())
			{
				IUCGameplayInterface::Execute_Interact(HitActor, InstigatorPawn);
				// DrawDebugSphere(GetWorld(), Hit.ImpactPoint, SphereRadius, 32, DebugLineColor, false, 2.f, 0, 2.f);
				break;
			}
		}
	}
	
}


void UUCInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUCInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

