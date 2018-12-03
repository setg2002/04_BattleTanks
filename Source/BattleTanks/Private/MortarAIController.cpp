// Copyright Notice

#include "MortarAIController.h"
#include "BattleTanks.h"
#include "MortarAimingComponent.h"

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledMortar = GetPawn();

	if (!ensure(PlayerTank && ControlledMortar)) { return; }

	// Aim towards player
	auto MortarAimingComponent = ControlledMortar->FindComponentByClass<UMortarAimingComponent>();
	MortarAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (MortarAimingComponent->GetFiringState() == EMortarFiringState::Locked)
	{
		MortarAimingComponent->Fire();
	}
}
