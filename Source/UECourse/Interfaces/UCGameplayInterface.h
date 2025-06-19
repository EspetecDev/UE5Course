
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UCGameplayInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUCGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

class UECOURSE_API IUCGameplayInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface|Gameplay")
	void Interact(APawn* InstingatorPawn);
};
