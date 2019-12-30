// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	//Max Force Per Tack (Newtons)
	//UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingFroce = 32000000; //40 000 000 for driffting 

	//UPROPERTY(EditDefaultsOnly)
		bool MoreSlippery = false;

private:
	UTankTracks();

	virtual void BeginPlay() override;
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();
	void DriveTrack();

	float CurrentThrottle = 0;
};
