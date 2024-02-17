// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/World/Spawning/SpawningSubsystem.h"

#include "Settings/UnrealCoreFrameworkSettings.h"

void USpawningSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing Spawning Subsystem") )
}

void USpawningSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Deinitializing Spawning Subsystem") )
}