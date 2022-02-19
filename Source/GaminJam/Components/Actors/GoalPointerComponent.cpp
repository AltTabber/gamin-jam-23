// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPointerComponent.h"

// Sets default values for this component's properties
UGoalPointerComponent::UGoalPointerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UGoalPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetPointerWidget->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TargetPointerWidget->SetRelativeLocation(FVector(0, 0, 0));
}


// Called every frame
void UGoalPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

