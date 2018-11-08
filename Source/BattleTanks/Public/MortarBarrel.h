// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MortarBarrel.generated.h"


UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UMortarBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 5; // Default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 85;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = -20;
};
