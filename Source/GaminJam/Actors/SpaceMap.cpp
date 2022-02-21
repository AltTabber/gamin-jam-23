// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMap.h"

#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"
#include "SceneManagement.h"

// Sets default values
ASpaceMap::ASpaceMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LineBatchComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatcher"));
	LineBatchComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpaceMap::BeginPlay()
{
	Super::BeginPlay();

	InitPlanets();

	uint8 send_data = MAX_uint8;

	UStaticMeshComponent* SunComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Sun")));
	UStaticMeshComponent* MarsComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mars")));
	UStaticMeshComponent* EarthComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Earth")));
	UStaticMeshComponent* VenusComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Venus")));
	UStaticMeshComponent* MercuryComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mercury")));

	FVector startLine = FVector(GetTransform().GetLocation());
	FVector endLine = FVector(GetTransform().GetLocation());
	endLine.Z = endLine.Z + 1000;
	
	LineBatchComponent->DrawLine(
		startLine,
		endLine,
		FLinearColor(0, 255, 0),
		send_data,
		2,
		2000
		);


	FVector planetLocation = FVector(SunComponent->GetComponentLocation());
	
	DrawCircle(
		GetWorld(),
		SunComponent->GetComponentLocation(),
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		FColor(0, 255, 0),
		988,
		100,
		false,
		10000,
		send_data,
		2
		);
	planetLocation = FVector(SunComponent->GetComponentLocation());
	planetLocation.X = planetLocation.X + 988;
	MarsComponent->SetWorldLocation(planetLocation);
	
	DrawCircle(
		GetWorld(),
		SunComponent->GetComponentLocation(),
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		FColor(0, 255, 0),
		650,
		100,
		false,
		10000,
		send_data,
		2
		);
	planetLocation = FVector(SunComponent->GetComponentLocation());
	planetLocation.X = planetLocation.X + 650;
	EarthComponent->SetWorldLocation(planetLocation);

	DrawCircle(
		GetWorld(),
		SunComponent->GetComponentLocation(),
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		FColor(0, 255, 0),
		468,
		100,
		false,
		10000,
		send_data,
		2
		);
	planetLocation = FVector(SunComponent->GetComponentLocation());
	planetLocation.X = planetLocation.X + 468;
	VenusComponent->SetWorldLocation(planetLocation);

	DrawCircle(
		GetWorld(),
		SunComponent->GetComponentLocation(),
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		FColor(0, 255, 0),
		251,
		100,
		false,
		10000,
		send_data,
		2
		);
	planetLocation = FVector(SunComponent->GetComponentLocation());
	planetLocation.X = planetLocation.X + 251;
	MercuryComponent->SetWorldLocation(planetLocation);
	
}

// Called every frame
void ASpaceMap::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	// cycle to all MapActors
	// move all MapActors
	// 
}

void ASpaceMap::InitPlanets()
{
	for(ASpaceMapActor* MapActor : ActorsOnMap)
	{
		//add actor to map
	}
}

void ASpaceMap::MovePlanets()
{
}

void ASpaceMap::DrawCircle(const UWorld* InWorld, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color,
	float Radius, int32 NumSides, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
{
	const float	AngleDelta = 2.0f * PI / NumSides;
	FVector	LastVertex = Base + X * Radius;

	TArray<FBatchedLine> Lines = TArray<FBatchedLine>();

	bool isVisible = true;

	for(int32 SideIndex = 0;SideIndex < NumSides;SideIndex++)
	{
		const FVector Vertex = Base + (X * FMath::Cos(AngleDelta * (SideIndex + 1)) + Y * FMath::Sin(AngleDelta * (SideIndex + 1))) * Radius;
		if(isVisible)
		{
			FBatchedLine Line = FBatchedLine(
				LastVertex,
				Vertex,
				Color,
				LifeTime,
				Thickness,
				DepthPriority);
			Lines.Add(Line);
			isVisible = false;
		}
		else
		{
			isVisible = true;
		}
		
		LastVertex = Vertex;
	}
	LineBatchComponent->DrawLines(Lines);
}


