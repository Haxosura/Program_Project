// Copyright Epic Games, Inc. All Rights Reserved.

#include "Program_ProjectGameMode.h"
#include "Program_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProgram_ProjectGameMode::AProgram_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
