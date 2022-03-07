// Fill out your copyright notice in the Description page of Project Settings.


#include "MapMovementController.h"

#include "Kismet/GameplayStatics.h"

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
	PlanetCoord = TMap<FString, FVector>();
	for(FGlobalMapObject GlobalObject : MapObjects)
	{
		PlanetCoord.Add(GlobalObject.Name, GlobalObject.GlobalLocation);
	}
}

// Called every frame
void AMapMovementController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPlayerOutOffBoundX();
	CheckPlayerOutOffBoundY();
	CheckPlayerOutOffBoundZ();

	// UE_LOG(LogTemp, Warning, TEXT("PlayerPosition - %s"), *PlayerPawn->GetTransform().GetLocation().ToString());
}

void AMapMovementController::CheckPlayerOutOffBoundX()
{
	if(PlayerPawn->GetTransform().GetLocation().X > X_BorderHigh)
	{
		PlayerPawn->AddActorWorldOffset(FVector(X_BorderLow - X_BorderHigh, 0, 0), false);
		AddPlayerGlobalLocationOffset(FVector(1, 0, 0));
		ManageSpawnOfObjects();
	}
	else if(PlayerPawn->GetTransform().GetLocation().X < X_BorderLow)
	{
		PlayerPawn->AddActorWorldOffset(FVector(X_BorderHigh - X_BorderLow, 0, 0), false);
		AddPlayerGlobalLocationOffset(FVector(-1, 0, 0));
		ManageSpawnOfObjects();
	}
}

void AMapMovementController::CheckPlayerOutOffBoundY()
{
	if(PlayerPawn->GetTransform().GetLocation().Y > Y_BorderHigh)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, Y_BorderLow - Y_BorderHigh, 0), false);
		AddPlayerGlobalLocationOffset(FVector(0, 1, 0));
		ManageSpawnOfObjects();
	}
	else if(PlayerPawn->GetTransform().GetLocation().Y < Y_BorderLow)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, Y_BorderHigh - Y_BorderLow, 0), false);
		AddPlayerGlobalLocationOffset(FVector(0, -1, 0));
		ManageSpawnOfObjects();
	}
}

void AMapMovementController::CheckPlayerOutOffBoundZ()
{
	if(PlayerPawn->GetTransform().GetLocation().Z > Z_BorderHigh)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, 0, Z_BorderLow - Z_BorderHigh), false);
		AddPlayerGlobalLocationOffset(FVector(0, 0, 1));
		ManageSpawnOfObjects();
	}
	else if(PlayerPawn->GetTransform().GetLocation().Z < Z_BorderLow)
	{
		PlayerPawn->AddActorWorldOffset(FVector(0, 0, Z_BorderHigh - Z_BorderLow), false);
		AddPlayerGlobalLocationOffset(FVector(0, 0, -1));
		ManageSpawnOfObjects();
	}
}

void AMapMovementController::AddPlayerGlobalLocationOffset(FVector Delta)
{
	PlayerGlobalLocation = PlayerGlobalLocation + Delta;
}

void AMapMovementController::ManageSpawnOfObjects()
{
	PrintDebugInfo();
	RemoveSpawnableObjectsFromScene();
	for(auto& Planet : PlanetCoord)
	{
		if(Planet.Value.Equals(PlayerGlobalLocation))
		{
			for(FGlobalMapObject MapObject : MapObjects)
			{
				if(MapObject.Name == Planet.Key)
				{
					SpawnObjectToScene(MapObject);					
				}
			}
		}
	}
}

void AMapMovementController::SpawnObjectToScene(FGlobalMapObject MapObject)
{
	GetWorld()->SpawnActor<ASpawnableObject>(MapObject.SpawnableObjectClass);
}

void AMapMovementController::RemoveSpawnableObjectsFromScene()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnableObject::StaticClass(), FoundActors);
	for(AActor* Actor : FoundActors)
	{
		Actor->Destroy();
	}
}

void AMapMovementController::SetGlobalLocation(FString Name, FVector _GlobalLocation)
{
	for(auto& MapObject : PlanetCoord)
	{
		if(MapObject.Key.Equals(Name))
		{
			MapObject.Value.Set(FMath::Floor(_GlobalLocation.X),
				FMath::Floor(_GlobalLocation.Y),
				FMath::Floor(_GlobalLocation.Z));
			// UE_LOG(LogTemp, Display, TEXT("Change Global Location %s - %s "), *MapObject.GlobalLocation.ToString(), *_GlobalLocation.ToString());
		}
	}
}

void AMapMovementController::PrintDebugInfo()
{
	UE_LOG(LogTemp, Display, TEXT("Change Global Location %s"), *PlayerGlobalLocation.ToString());
	for(auto& MapObject : PlanetCoord)
	{
		UE_LOG(LogTemp, Display, TEXT("Planet %s location - %s"), *MapObject.Key, *MapObject.Value.ToString());
	}
}

