// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceMapActor.h"
#include "Camera/CameraActor.h"
#include "GameFramework/Actor.h"
#include "SpaceMap.generated.h"

UCLASS()
class GAMINJAM_API ASpaceMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceMap();
	ULineBatchComponent* LineBatchComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitPlanets();
	void MovePlanets();
	void DrawCircle(const UWorld* InWorld, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color,
	                float Radius, int32 NumSides, bool bPersistentLines, float LifeTime, uint8 DepthPriority,
	                float Thickness);
	void InitMars();
	void InitEarth();
	void InitVenus();
	void InitMercury();
	void InitMeteorite();
	void InitPlanet(int32 Radius, UStaticMeshComponent* Planet, float angle);
	void RotatePlanet(int32 Radius, UStaticMeshComponent* Planet, float Angle);
	void DrawRootCurve(const UWorld* InWorld, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color,
		float Radius, int32 NumSides, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
	void RotateMars();
	void RotateEarth();
	void RotateVenus();
	void RotateMercury();
	
	UCameraComponent* Camera;

	UStaticMeshComponent* SunComponent;
	UStaticMeshComponent* MarsComponent; 
	UStaticMeshComponent* EarthComponent;
	UStaticMeshComponent* VenusComponent;
	UStaticMeshComponent* MercuryComponent;

	UPROPERTY(EditAnywhere) float MarsRadius = 988;
	UPROPERTY(EditAnywhere) float EarthRadius = 650;
	UPROPERTY(EditAnywhere) float VenusRadius = 468;
	UPROPERTY(EditAnywhere) float MercuryRadius = 251;

	UPROPERTY(EditAnywhere) float MarsAngleSpeed = 45;
	UPROPERTY(EditAnywhere) float EarthAngleSpeed = 50;
	UPROPERTY(EditAnywhere) float VenusAngleSpeed = 60;
	UPROPERTY(EditAnywhere) float MercuryAngleSpeed = 75;
	
	uint8 send_data = MAX_uint8;

	TArray<ASpaceMapActor*> ActorsOnMap = TArray<ASpaceMapActor*>();  

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UCameraComponent* GetCamera();
};
