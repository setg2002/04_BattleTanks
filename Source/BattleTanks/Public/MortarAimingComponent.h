// Copyright Notice

#pragma once

#include "kismet/GamePlayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MortarAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EMortarFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward Declarations
class UMortarBarrel;
class UMortarTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UMortarAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UMortarBarrel* MortarBarrelToSet, UMortarTurret* MortarTurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EMortarFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EMortarFiringState FiringState = EMortarFiringState::Reloading;


private:
	// Sets default values for this component's properties
	UMortarAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFuncion) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UMortarBarrel* MortarBarrel = nullptr;
	UMortarTurret* MortarTurret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 150000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 10;

	double LastFireTime = 0;

	FVector AimDirection;

	int RoundsLeft = 5;
};
