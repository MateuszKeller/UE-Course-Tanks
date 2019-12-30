// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }

	LeftTrack = LeftTrackToSet;
	LeftTrack->TrackMaxDrivingFroce = TrackMaxDrivingFroce;
	LeftTrack->MoreSlippery = MoreSlippery;

	RightTrack = RightTrackToSet;
	RightTrack->TrackMaxDrivingFroce = TrackMaxDrivingFroce;
	RightTrack->MoreSlippery = MoreSlippery;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankCurrentForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // Vector Tank is currently facing
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // Vector AI woud like to be headed

	float ForwardThrow = FVector::DotProduct(TankCurrentForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankCurrentForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}
