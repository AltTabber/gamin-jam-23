// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMap.h"

#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"
#include "SceneManagement.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"

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

	SunComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Sun")));
	MarsComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mars")));
	EarthComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Earth")));
	VenusComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Venus")));
	MercuryComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mercury")));
	Camera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("Camera")));

	InitPlanets();
	
}

// Called every frame
void ASpaceMap::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	MovePlanets();
	
}

void ASpaceMap::InitPlanets()
{
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
	
	InitMars();
	InitEarth();
	InitVenus();
	InitMercury();
	
	DrawRootCurve(
		GetWorld(),
    	SunComponent->GetComponentLocation() - FVector(MarsRadius*1.5, MarsRadius*0.3, 0),
    	FVector(1, 0, 0),
    	FVector(0, 1, 0),
    	FColor(0, 255, 0),
    	0,
    	100,
    	false,
    	10000,
    	send_data,
    	3
	);
}

void ASpaceMap::MovePlanets()
{
	RotateMars();
	RotateEarth();
	RotateVenus();
	RotateMercury();
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

UCameraComponent* ASpaceMap::GetCamera()
{
	return Camera;
}

void ASpaceMap::InitMars()
{
	ASpaceMap::InitPlanet(MarsRadius, MarsComponent, 0);
}

void ASpaceMap::InitEarth()
{
	ASpaceMap::InitPlanet(EarthRadius, EarthComponent, 45);
}

void ASpaceMap::InitVenus()
{
	ASpaceMap::InitPlanet(VenusRadius, VenusComponent, 90);
}

void ASpaceMap::InitMercury()
{
	ASpaceMap::InitPlanet(MercuryRadius, MercuryComponent, 180);
}

void ASpaceMap::InitMeteorite()
{
	
}

void ASpaceMap::DrawRootCurve(const UWorld* InWorld, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color,
	float Radius, int32 NumSides, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
{
	const float	AngleDelta = 2.0f * PI / NumSides;
	FVector	LastVertex = Base;

	TArray<FBatchedLine> Lines = TArray<FBatchedLine>();

	float PointCounter = 0; 
	TArray<FVector> Points = TArray<FVector>();
	for(int32 SideIndex = 0;SideIndex < NumSides;SideIndex++)
	{
		FVector Point = FVector(PointCounter, FMath::Sqrt(PointCounter), 0);
		PointCounter+=0.1f;
		Points.Add(Point);
	}

	bool isVisible = true;

	for(FVector Point : Points)
	{
		const FVector Vertex = Base + Point*500;
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

void ASpaceMap::InitPlanet(int32 Radius, UStaticMeshComponent* Planet, float angle)
{
	FVector planetLocation = FVector(SunComponent->GetComponentLocation());
	
	DrawCircle(
		GetWorld(),
		SunComponent->GetComponentLocation(),
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		FColor(0, 255, 0),
		Radius,
		100,
		false,
		10000,
		send_data,
		3
		);
	RotatePlanet(Radius, Planet, angle);
}

void ASpaceMap::RotatePlanet(int32 Radius, UStaticMeshComponent* Planet, float Angle)
{
	FVector PlanetLocation = FVector(SunComponent->GetComponentLocation());
	
	FRotator Rotator = FRotator(0, Angle, 0);
	FVector RotationVector = Rotator.RotateVector(FVector(1, 0, 0));
	PlanetLocation.X = PlanetLocation.X + Radius*RotationVector.X;
	PlanetLocation.Y = PlanetLocation.Y + Radius*RotationVector.Y;
	Planet->SetWorldLocation(PlanetLocation);
}

void ASpaceMap::RotateMars()
{
	RotatePlanet(MarsRadius, MarsComponent, MarsAngleSpeed * GetWorld()->GetRealTimeSeconds());
}

void ASpaceMap::RotateEarth()
{
	RotatePlanet(EarthRadius, EarthComponent, EarthAngleSpeed * GetWorld()->GetRealTimeSeconds());
}

void ASpaceMap::RotateVenus()
{
	RotatePlanet(VenusRadius, VenusComponent, VenusAngleSpeed * GetWorld()->GetRealTimeSeconds());
}

void ASpaceMap::RotateMercury()
{
	RotatePlanet(MercuryRadius, MercuryComponent, MercuryAngleSpeed * GetWorld()->GetRealTimeSeconds());
}
