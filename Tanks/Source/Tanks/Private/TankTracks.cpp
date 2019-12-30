// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (MoreSlippery) return;
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()* CorrectionAcceleration / 2; //  divided by 2 'cause there are 2 tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingFroce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
