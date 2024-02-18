// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/Base/CoreTickableWorldSubsystem.h"

DEFINE_LOG_CATEGORY(LogTickableWorldSubsystem);

void UCoreTickableWorldSubsystem::PreInitialize()
{
}

void UCoreTickableWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	PreInitialize();
	Super::Initialize(Collection);
	UE_LOG(LogTickableWorldSubsystem, Log, TEXT("Initialize UCoreTickableWorldSubsystem"));
}

void UCoreTickableWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCoreTickableWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UCoreTickableWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTickableWorldSubsystem, Log, TEXT("Deinitialize UCoreTickableWorldSubsystem"));
}
