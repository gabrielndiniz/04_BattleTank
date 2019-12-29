// Fill out your copyright notice in the Description page of Project Settings.


#include "Public\TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledAITank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *ControlledTank->GetName());
	}
}

ATank* ATankAIController::GetControlledAITank() const {

	return Cast<ATank>(GetPawn());
}