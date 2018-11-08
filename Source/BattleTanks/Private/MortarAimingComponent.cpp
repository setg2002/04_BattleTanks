// Copyright Notice

#include "MortarAimingComponent.h"
#include "BattleTanks.h"
#include "MortarBarrel.h"
#include "MortarTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UMortarAimingComponent::UMortarAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMortarAimingComponent::BeginPlay()
{
	// So that first is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UMortarAimingComponent::Initialize(UMortarBarrel* MortarBarrelToSet, UMortarTurret* MortarTurretToSet)
{
	MortarBarrel = MortarBarrelToSet;
	MortarTurret = MortarTurretToSet;
}

void UMortarAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFuncion)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EMortarFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EMortarFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EMortarFiringState::Aiming;
	}
	else
	{
		FiringState = EMortarFiringState::Locked;
	}
}

int UMortarAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EMortarFiringState UMortarAimingComponent::GetFiringState() const
{
	return FiringState;
}


bool UMortarAimingComponent::IsBarrelMoving()
{
	if (!ensure(MortarBarrel)) { return false; }
	auto BarrelForward = MortarBarrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // Vectors are equal
}

void UMortarAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(MortarBarrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = MortarBarrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		true,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	); // Calculate OutLaunchVelocity
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	// If no soution found do nothing
}

void UMortarAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(MortarBarrel) || !ensure(MortarTurret)) { return; }

	auto BarrelRotator = MortarBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Always yaw the shortest way
	MortarBarrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		MortarTurret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		MortarTurret->Rotate(-DeltaRotator.Yaw);
	}
}

void UMortarAimingComponent::Fire()
{
	if (FiringState == EMortarFiringState::Locked || FiringState == EMortarFiringState::Aiming)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(MortarBarrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile1 = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			MortarBarrel->GetSocketLocation(FName("Projectile_1")),
			MortarBarrel->GetSocketRotation(FName("Projectile_1"))
			);
		Projectile1->LaunchProjectile(LaunchSpeed);

		auto Projectile2 = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			MortarBarrel->GetSocketLocation(FName("Projectile_2")),
			MortarBarrel->GetSocketRotation(FName("Projectile_2"))
			);
		Projectile2->LaunchProjectile(LaunchSpeed);

		auto Projectile3 = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			MortarBarrel->GetSocketLocation(FName("Projectile_3")),
			MortarBarrel->GetSocketRotation(FName("Projectile_3"))
			);
		Projectile3->LaunchProjectile(LaunchSpeed);
		
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}
