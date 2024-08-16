// Copyright Epic Games, Inc. All Rights Reserved.

#include "codestoryGameMode.h"
#include "codestoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AcodestoryGameMode::AcodestoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Hero/MyHero"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
