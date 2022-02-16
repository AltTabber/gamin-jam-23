// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "PlayerPawnController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMINJAM_API UPlayerPawnController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerPawnController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector AbsoluteLocation;
	FVector TickMove;
	float Speed = 0.f;
	float SpeedAxis = 0.f;
	FVector SceneLocation;
	FVector SceneLocationDelta;
	FRotator SceneRotator;

	UPROPERTY(EditAnywhere) float AccelerationEngine1 = 100.f;
	
	UInputComponent* InputComponent;
	UArrowComponent* Arrow;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void InitPlayerInput();
	
	void MovePlayer(float DeltaTime);
	void SetSpeed(float DeltaTime);
	
	void SpeedChange(float Axis);
	
};
