// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapMovementController.generated.h"

USTRUCT()
struct FGlobalMapObject
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere) FString Name;
	UPROPERTY(EditAnywhere) FVector GlobalLocation;

	FGlobalMapObject(const FString& Name, const FVector& GlobalLocation)
		: Name(Name),
		  GlobalLocation(GlobalLocation)
	{
	}
};

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

	UPROPERTY(EditAnywhere) FVector PlayerGlobalLocation;
	UPROPERTY(EditAnywhere) FVector SunGlobalLocation;
	UPROPERTY(EditAnywhere) FVector MercuryGlobalLocation;
	UPROPERTY(EditAnywhere) FVector VenusGlobalLocation;
	UPROPERTY(EditAnywhere) FVector EarthGlobalLocation;
	UPROPERTY(EditAnywhere) FVector MarsGlobalLocation = FVector(30, 20, 1);

	UPROPERTY(EditAnywhere) TArray<FGlobalMapObject> MapObjects =
		TArray<FGlobalMapObject>();
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CheckPlayerOutOffBoundX();
	void CheckPlayerOutOffBoundY();
	void CheckPlayerOutOffBoundZ();
	void AddPlayerGlobalLocationOffset(FVector Delta);
	void ManageSpawnOfObjects();
	

};
