// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PLayerControler not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PLayerControler possesing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshaid();

}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshaid()
{
	if (!GetControlledTank()) return;

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//Finding the crosshair position in Viewport
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	FVector LookDirection;
	//De-project the screen position of the crosshair to a world direction
	if (GetLookDirection(CrosshairLocation, LookDirection))
	{
		//Line-trace along that LookDirection and see what we hit
		GetLookVectorHitLocation(LookDirection, OutHitLocation);		
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D &CrosshairLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; // discarded - not needed in this case
	return DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation+ LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}
