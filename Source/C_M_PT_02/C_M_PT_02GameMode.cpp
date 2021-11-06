// Copyright Epic Games, Inc. All Rights Reserved.

#include "C_M_PT_02GameMode.h"
#include "C_M_PT_02Character.h"
#include "UObject/ConstructorHelpers.h"

AC_M_PT_02GameMode::AC_M_PT_02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
