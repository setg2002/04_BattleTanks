// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TankTrack is used to set a maxinum driving force, and to apply forces to the tank
 */

UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//TODO Make tracks take damage seperatly from tank body
	// Called by the engine when damage is dealt to ACTOR not StaticMeshComponent
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	FVector CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxSpeed = 800.f;

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 4000000; // Assume 40 tonne tank, and 1g accelleration
	
private:
	UTankTrack();

	/*UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingTrackHealth = 50;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingTrackHealth;*/

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;
};
