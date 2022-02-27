// Copyright Epic Games, Inc. All Rights Reserved.

#include "GaminJamGameMode.h"
#include "GaminJamPawn.h"

AGaminJamGameMode::AGaminJamGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AGaminJamPawn::StaticClass();

	
}
