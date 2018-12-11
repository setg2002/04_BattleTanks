// Copyright Notice

#include "MortarAIController.h"
#include "BattleTanks.h"
#include "MortarAimingComponent.h"
#include "Tank.h"

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMortarAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedMortar = Cast<ATank>(InPawn);
		if (!ensure(PossessedMortar)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedMortar->OnDeath.AddUniqueDynamic(this, &AMortarAIController::OnPossessedMortarDeath);
	}
}

void AMortarAIController::OnPossessedMortarDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
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
