// Fill out your copyright notice in the Description page of Project Settings.


#include "MapMovementController.h"

// Sets default values
AMapMovementController::AMapMovementController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapMovementController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator();
}

// Called every frame
void AMapMovementController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPlayerOutOffBoundX();
	CheckPlayerOutOffBoundY();
	CheckPlayerOutOffBoundZ();

	UE_LOG(LogTemp, Warning, TEXT("PlayerPosition - %s"), *PlayerPawn->GetTransform().GetLocation().ToString());
}

void AMapMovementController::CheckPlayerOutOffBoundX() const
{
	if(PlayerPawn->GetTransform().GetLocation().X > X_BorderHigh)
	{
		PlayerPawn->AddActorWorldOffset(FVector(X_BorderLow - X_BorderHigh, 0, 0), false);
	}
	else if(PlayerPawn->GetTransform().GetLocation().X < X_BorderLow)
	{
		PlayerPawn->AddActorWorldOffset(FVector(X_BorderHigh - X_BorderLow, 0, 0), false);
	}
}

void AMapMovementController::CheckPlayerOutOffBoundY() const
{
	if(PlayerPawn->GetTransform().GetLocation().Y > Y_BorderHigh)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, Y_BorderLow - Y_BorderHigh, 0), false);
	}
	else if(PlayerPawn->GetTransform().GetLocation().Y < Y_BorderLow)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, Y_BorderHigh - Y_BorderLow, 0), false);
	}
}

void AMapMovementController::CheckPlayerOutOffBoundZ() const
{
	if(PlayerPawn->GetTransform().GetLocation().Z > Z_BorderHigh)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, 0, Z_BorderLow - Z_BorderHigh), false);
	}
	else if(PlayerPawn->GetTransform().GetLocation().Z < Z_BorderLow)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, 0, Z_BorderHigh - Z_BorderLow), false);
	}
}
