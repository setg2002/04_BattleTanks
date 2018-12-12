// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SpringWheel.generated.h"


UCLASS()
class BATTLETANKS_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void AddDrivingForce(float ForceMagnitude);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void SetupConstraint();

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
};
