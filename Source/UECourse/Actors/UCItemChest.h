#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UECourse/Interfaces/UCGameplayInterface.h"
#include "UCItemChest.generated.h"

UCLASS()
class UECOURSE_API AUCItemChest : public AActor, public IUCGameplayInterface
{
	GENERATED_BODY()

public:

	AUCItemChest();
	
	virtual void Interact_Implementation(APawn* InstingatorPawn) override;

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> LidMesh = nullptr;

	UPROPERTY(EditAnywhere)
	float TargetPitch = 110.f;
	
protected:

	virtual void BeginPlay() override;

};
