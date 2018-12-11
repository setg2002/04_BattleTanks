// Copyright Notice

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "kismet/GamePlayStatics.h"
#include "WheelSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UWheelSpawnPoint : public USceneComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UWheelSpawnPoint();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	// Config
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;
};
