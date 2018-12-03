// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10; // Default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 35;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = -2;
};
