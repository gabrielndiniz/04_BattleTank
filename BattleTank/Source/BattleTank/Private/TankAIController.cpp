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

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not located player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController located player tank"));
	}
}

ATank* ATankAIController::GetControlledAITank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	else {
		return Cast<ATank>(PlayerPawn);
	}
	
}
