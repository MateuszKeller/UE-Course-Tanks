// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	//Called by the engine when actor damage is dealt 
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	//Returns current health percentage
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	FTankDelegate OnDeath;
private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth;
};
