// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
}