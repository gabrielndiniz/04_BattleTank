// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/PlayerCameraManager.h"
#include "Math/TransformNonVectorized.h"
#include "BattleTank.h"
#include "Public/Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) { // Has "side-effect", is going to line trace
		UE_LOG(LogTemp, Warning, TEXT("Aim with %s"), *HitLocation.ToString());
		//TODO aim at that point
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Aim the Sky"));
	}
	//Get world location if linetrace through crosshair
		//if it hits the landscape
		//Tell controlled tank to aim at this point

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}