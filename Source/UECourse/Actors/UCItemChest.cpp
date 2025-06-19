// Fill out your copyright notice in the Description page of Project Settings.


#include "UCItemChest.h"


// Sets default values
AUCItemChest::AUCItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(RootComponent);
}

void AUCItemChest::Interact_Implementation(APawn* InstingatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AUCItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}
