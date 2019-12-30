// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:

	//Move the tank barrel so thaht shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	//True if hit landscape
	bool GetSightRayHitLocation(FVector&) const;

	bool GetLookDirection(FVector2D &CrosshairLocation, FVector &WorldDirection) const;

	bool GetLookVectorHitLocation(FVector, FVector&) const;
	
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;
};
