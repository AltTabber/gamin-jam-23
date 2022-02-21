// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetOffScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMINJAM_API UTargetOffScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable) FString AddGoalPointer();
	
	
};
