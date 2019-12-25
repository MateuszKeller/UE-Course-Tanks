// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; 
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY(EditAnywhere)
		bool bDrawDebugLine = false;

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

public:	
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void Move(FVector AimDirection);
};
