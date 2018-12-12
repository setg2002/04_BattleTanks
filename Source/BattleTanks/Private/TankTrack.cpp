// Copyright Notice

#include "TankTrack.h"
#include "SpringWheel.h"
#include "WheelSpawnPoint.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<class ASpringWheel*> UTankTrack::GetWheels() const
{
	TArray<class ASpringWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<UWheelSpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChiled = SpawnPointChild->GetSpawnedActor();
		auto SpringWheel = Cast<ASpringWheel>(SpawnedChiled);
		if (!SpringWheel) continue;

		ResultArray.Add(SpringWheel);
	}
	return ResultArray;
}


/*float UTankTrack::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Track Hit"))
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Track died"))
		DestroyComponent();
	}
	return DamageToApply;
}*/

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	CurrentSpeed = GetComponentVelocity().X;

	if ((CurrentSpeed < MaxSpeed) && (CurrentSpeed > -MaxSpeed))
	{
		auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
		auto Wheels = GetWheels();
		auto ForcePerWheel = ForceApplied /*/ Wheels.Num()*/;
		for (ASpringWheel* Wheel : Wheels)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}
