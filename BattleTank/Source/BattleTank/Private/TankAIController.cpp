// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAIController.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if(PlayerTank) {
		FVector HitLocation;

		//TODO move towards the player

		// Aim towards the Player

		HitLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(HitLocation);

		// Fire if ready
		ControlledTank->Fire(); //TODO limit firing rate
		
	}
}