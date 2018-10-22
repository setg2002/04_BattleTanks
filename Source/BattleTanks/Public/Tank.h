// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// Forward Declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;



UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	virtual void BeginPlay() override;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Local barrel refernce for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO Remove

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 6000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};
