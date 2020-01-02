// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Public/Tank.h"



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
		GetControlledTank()->AimAt(HitLocation);
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

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction, and see what we hit (up to max range)
		FVector HitLocation;
		GetLookVectorHitLocation(LookDirection, HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("HitResult: %s"), *HitLocation.ToString());
		OutHitLocation = HitLocation;
	}

	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector  CameraWorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld( //this function changed, from version
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	//FVector Start = GetWorld()->GetFirstPlayerController()->GetPawn()->GetAttachParentSocketName()->
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	FVector LineTraceEnd = PlayerViewPointLocation +
		LineTraceRange * LookDirection;

	/*DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);*/

	

	//FVector StartLocation = PlayerCameraManager->GetCameraLocation();

	//FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	//UE_LOG(LogTemp, Warning, TEXT("PlayerViewPointLocation:%s aim LineTraceEnd: %s"), *PlayerViewPointLocation.ToString(), *LineTraceEnd.ToString());

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PlayerViewPointLocation, //Can be PlayerViewPointLocation
		LineTraceEnd, //Can be LineTraceEnd
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation=HitResult.Location;
		return true;
	}
	else { 
		HitLocation.X = 0;
		HitLocation.Y = 0;
		HitLocation.Z = 0;
		return false; }
	;

	//DrawDebugLine(
	//	GetWorld(),
	//	StartLocation,
	//	EndLocation,
	//	FColor(255, 0, 0),
	//	false,
	//	0.f,
	//	0.f,
	//	10.f
	//);
	
}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}