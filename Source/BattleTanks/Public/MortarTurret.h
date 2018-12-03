// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MortarTurret.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UMortarTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max up movement
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 10; // Default
};