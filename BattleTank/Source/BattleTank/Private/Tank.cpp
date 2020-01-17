// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Public/Tank.h"
#include "Public/Projectile.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankPlayerController.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

//void ATank::AimAt(FVector HitLocation)
//{
//	auto OurTankName = GetName();
//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString());
//
//}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();


}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;

}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);

}

void ATank::SetTrackReference(UTankTrack* TrackToSet)
{
	//TankAimingComponent->SetTrackReference(TrackToSet);

}

void ATank::Fire()
{
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && isReloaded) {

		//Spawn the projectile at the end of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
