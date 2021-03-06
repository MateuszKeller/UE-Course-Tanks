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
class AProjectile;

UENUM()
enum class EFiringState: uint8
{
	Locked,
	Aiming,
	Reloading,
	NoAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
		bool bDrawDebugLine = false;

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	// GET/SET
	EFiringState GetFiringState() const { return FiringState; }

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetAmmo() const { return Ammo; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = Setup)
		EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	void Move(FVector AimDirection);

	bool isBarrelMoving();

	FVector AimDirection;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	//EditAnywhere - we can set property for every instance separately; EditDefaultsOnly - we can change property only for BP
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 6000;

	UPROPERTY(EditAnywhere, Category = Firing)
		float ReloadTimeInS = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;
	
	double LastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	int32 Ammo = 15;
};
