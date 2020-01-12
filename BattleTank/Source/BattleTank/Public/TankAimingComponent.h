// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UStaticMeshComponent * Barrel = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	//TODO add SetTurretReference

	UPROPERTY(EditAnywhere)
	float ProjectileRadius = 10.f;

	UPROPERTY(EditAnywhere)
	float OverrideGravityZ = 0.f;
		
	void MoveBarrelTowards(FVector AimDirection);
};
