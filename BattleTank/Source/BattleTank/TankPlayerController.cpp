// Fill out your copyright notice in the Description page of Project Settings.


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
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
		//TODO aim at that point
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Aim the Sky"));
	}
	//Get world location if linetrace through crosshair
		//if it hits the landscape
		//Tell controlled tank to aim at this point

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); 

	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	//"De-project" the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to max range)
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}