// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

 //Forward Declaration
class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	void AimAt(FVector HitLocation);

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000.f; // TODO find something reasonable

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;


private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Sets default values for this pawn's properties
	ATank();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
};
