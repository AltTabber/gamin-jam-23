// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"
#include "Gaminjam/Actors/MeteoreEngine.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

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

	if(!YawInvert)
	{
		invertMultiplier = -1.0;
	}

	TArray<AActor*> SpaceMapArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpaceMap::StaticClass(), SpaceMapArr);
	for(AActor* MapElem: SpaceMapArr)
	{
		SpaceMap = Cast<ASpaceMap>(MapElem);
	}

	CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
}


// Called every frame
void UPlayerPawnController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SceneLocation = GetOwner()->GetActorTransform().GetLocation();
	SceneRotator = GetOwner()->GetActorRotation();

	MovePlayer(DeltaTime);
	
}

void UPlayerPawnController::InitPlayerInput()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent){
		UE_LOG(LogTemp, Warning, TEXT("Found component UInputComponent in Actor %s"), *GetOwner()->GetName());
		InputComponent->BindAxis("SpeedChange", this, &UPlayerPawnController::SpeedChange);
		InputComponent->BindAxis("Turn", this, &UPlayerPawnController::TurnChange);
		InputComponent->BindAxis("Rotate", this, &UPlayerPawnController::RotateChange);
		InputComponent->BindAxis("MoveUp", this, &UPlayerPawnController::YawChange);
		InputComponent->BindAction("MapAction", IE_Pressed, this, &UPlayerPawnController::MapAction);
		InputComponent->BindAction("CreateMeteoreEngine", IE_Pressed, this, &UPlayerPawnController::CreateMeteoreEngine);
	}else{
		UE_LOG(LogTemp, Error, TEXT("Found component UInputComponent in Actor %s"), *GetOwner()->GetName());
	}
}

void UPlayerPawnController::SpeedChange(float Axis)
{
	SpeedAxis = Axis;

	CurrentSpeed += SpeedAxis * AccelerationEngine1 * GetWorld()->GetDeltaSeconds();
}

void UPlayerPawnController::YawChange(float Axis)
{

	Axis = invertMultiplier * Axis;
	
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Axis * YawSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);
	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void UPlayerPawnController::RotateChange(float Axis)
{
	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value.
	float TargetRollSpeed = (Axis * RollSpeed);
	
	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void UPlayerPawnController::TurnChange(float Axis)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Axis * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// const bool bIsTurning = FMath::Abs(Axis) > 0.2f;
	// // If turning, yaw value is used to influence roll
	// // If not turning, roll to reverse current roll value.
	// float TargetRollSpeed = bIsTurning ?
	// 	(invertMultiplier * CurrentYawSpeed * 0.5f) :
	// 	(invertMultiplier * SceneRotator.Roll * -2.f);
	//
	// // Smoothly interpolate roll speed
	// CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}


void UPlayerPawnController::MovePlayer(float DeltaTime)
{
	const FVector LocalMove = FVector(CurrentSpeed * DeltaTime, 0.f, 0.f);
	
	GetOwner()->AddActorLocalOffset(LocalMove, true);

	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;

	GetOwner()->AddActorLocalRotation(DeltaRotation);
}

void UPlayerPawnController::MapAction()
{
	if(!IsMapOpened)
	{
		IsMapOpened = true;
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(SpaceMap);
	}
	else
	{
		IsMapOpened = false;
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this->GetOwner());
	}
}
void UPlayerPawnController::CreateMeteoreEngine()
{
	FVector SpawnLocation = GetOwner()->GetTransform().GetLocation();
	FRotator SpawnRotation = GetOwner()->GetActorRotation();

	GetWorld()->SpawnActor<AMeteoreEngine>(SpawnLocation,SpawnRotation);
}
