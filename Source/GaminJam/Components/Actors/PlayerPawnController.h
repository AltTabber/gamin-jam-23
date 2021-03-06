// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "GaminJam/Actors/SpaceMap.h"
#include "PlayerPawnController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMINJAM_API UPlayerPawnController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerPawnController();

	//UFUNCTION()
	void CreateMeteoreEngine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector AbsoluteLocation;
	FVector TickMove;

	UPROPERTY(BlueprintReadOnly) float CurrentSpeed = 0.f;
	
	float CurrentYawSpeed = 0.f;
	float CurrentPitchSpeed = 0.f;
	float CurrentRollSpeed = 0.f;
	float SpeedAxis = 0.f;
	FVector SceneLocation;
	FVector SceneLocationDelta;
	FRotator SceneRotator;

	UPROPERTY(EditAnywhere) float AccelerationEngine1 = 400.f;
	UPROPERTY(EditAnywhere) float SpeedMaxEngine1 = 1000.f;
	UPROPERTY(EditAnywhere) float SpeedMinEngine1 = 0.f;
	UPROPERTY(EditAnywhere) float YawSpeed = 70.f;
	UPROPERTY(EditAnywhere) float TurnSpeed = 50.f;
	UPROPERTY(EditAnywhere) float RollSpeed = 70.f;
	UPROPERTY(EditAnywhere) float RotateSpeed = 70.f;
	UPROPERTY(EditAnywhere) bool YawInvert = false;

	UPROPERTY(EditAnywhere) ASpaceMap* SpaceMap;
	
	bool IsMapOpened = false;

	int32 invertMultiplier = 1.0f;
	
	UInputComponent* InputComponent;
	UArrowComponent* Arrow;
	UCameraComponent* CameraComponent;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void InitPlayerInput();
	
	void MovePlayer(float DeltaTime);
	
	void SpeedChange(float Axis);
	void YawChange(float Axis);
	void RotateChange(float Axis);
	void TurnChange(float Axis);

	void MapAction();
	
};
