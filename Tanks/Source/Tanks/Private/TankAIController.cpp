// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerPawn = GetPlayerTank();
	
	if (!ensure(PlayerPawn && GetPawn())) return;
	
	// Move towards player
	MoveToActor(PlayerPawn, AcceptanceRadius);

	//Aim towards player
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
		//GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());
	//Fire if ready
	AimingComponent->Fire();
	

}

APawn * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerPawn)) return nullptr;

	return PlayerPawn;
}
