// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h" 
#include "Projectile.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInS)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (isBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel)) return;

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation,
		WorldSpaceAim, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace
						,FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), bDrawDebugLine);
	// Calculate the OutLaunchVelocity
	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal(); // Turining to unit vector
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *(GetOwner()->GetName()), *AimDirection.ToString());
		Move(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState!= EFiringState::Reloading)
	{
		if (!ensure(Barrel && ProjectileBP)) return;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::Move(FVector AimDirection)
{

	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//Calculate difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("Delta Rotation: %s"), *DeltaRotator.ToString());
	//Move the Barrel
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

	
}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
}

