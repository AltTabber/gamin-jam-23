// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMapActor.h"

#include "Components/LineBatchComponent.h"

// Sets default values
ASpaceMapActor::ASpaceMapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpaceMapActor::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ASpaceMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

