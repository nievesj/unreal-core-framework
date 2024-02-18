// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Base/CoreGameMode.h"

#include "Kismet/GameplayStatics.h"

void ACoreGameMode::InitGameState()
{
	// Set Default Pawn
	if (PlayerPawnClass)
	{
		if (UClass* PawnClass = PlayerPawnClass.Get())
		{
			DefaultPawnClass = PawnClass;
		}
	}

	Super::InitGameState();
	OnGameStateInitialized();
}

void ACoreGameMode::OnGameStateInitialized()
{
}
