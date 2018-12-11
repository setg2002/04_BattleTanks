// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

/**
 * 
 */

 // Forward declarations
class ATank;

UCLASS()
class BATTLETANKS_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossessedMortarDeath();
};
