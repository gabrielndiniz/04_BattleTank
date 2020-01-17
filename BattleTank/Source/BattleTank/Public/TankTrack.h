// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


/*TankTrack us ysed ti set naxunyn driving force and apply to move the tank
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	

	//TODO clamp actual throttle value so player can't over-dride
};
