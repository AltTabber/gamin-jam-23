// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceMapActor.generated.h"

UCLASS()
class GAMINJAM_API ASpaceMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceMapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector BeginLocation;
	FVector Location;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
