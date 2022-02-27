// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapMovementController.generated.h"

UCLASS()
class GAMINJAM_API AMapMovementController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapMovementController();
	
	UPROPERTY(EditAnywhere) float X_BorderLow = -1000000.f;
	UPROPERTY(EditAnywhere) float X_BorderHigh = 1000000.f;
	UPROPERTY(EditAnywhere) float Y_BorderLow = -1000000.f;
	UPROPERTY(EditAnywhere) float Y_BorderHigh = 1000000.f;
	UPROPERTY(EditAnywhere) float Z_BorderLow = -1000000.f;
	UPROPERTY(EditAnywhere) float Z_BorderHigh = 1000000.f;

	UPROPERTY(EditAnywhere) APawn* PlayerPawn;

	FVector CurrentLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CheckPlayerOutOffBoundX() const;
	void CheckPlayerOutOffBoundY() const;
	void CheckPlayerOutOffBoundZ() const;
	void SetNewLocation();

	

};
