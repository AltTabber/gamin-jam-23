// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"

#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UPlayerPawnController::UPlayerPawnController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerPawnController::BeginPlay()
{
	Super::BeginPlay();

	InitPlayerInput();
	Arrow = GetOwner()->FindComponentByClass<UArrowComponent>();
	
}


// Called every frame
void UPlayerPawnController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SceneLocation = GetOwner()->GetActorTransform().GetLocation();
	SceneRotator = Arrow->GetRelativeRotation();

	SetSpeed(DeltaTime);
	MovePlayer(DeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed: %f, CurrentLocation: %s, CurrentRotation: %s"),
		Speed, *SceneLocation.ToString(), *SceneRotator.ToString());
}

void UPlayerPawnController::InitPlayerInput()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent){
		UE_LOG(LogTemp, Warning, TEXT("Found component UInputComponent in Actor %s"), *GetOwner()->GetName());
		InputComponent->BindAxis("SpeedChange", this, &UPlayerPawnController::SpeedChange);
	}else{
		UE_LOG(LogTemp, Error, TEXT("Found component UInputComponent in Actor %s"), *GetOwner()->GetName());
	}
}

void UPlayerPawnController::SpeedChange(float Axis)
{
	SpeedAxis = Axis;
}

void UPlayerPawnController::MovePlayer(float DeltaTime)
{
	
	SceneLocationDelta = SceneRotator.Vector() * Speed * DeltaTime;
	
	GetOwner()->AddActorLocalOffset(SceneLocationDelta, true);
}

void UPlayerPawnController::SetSpeed(float DeltaTime)
{
	Speed += SpeedAxis * AccelerationEngine1 * DeltaTime;	
}