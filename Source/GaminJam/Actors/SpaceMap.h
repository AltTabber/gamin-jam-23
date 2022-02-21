// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceMapActor.h"
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

	TArray<ASpaceMapActor*> ActorsOnMap = TArray<ASpaceMapActor*>();  

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
