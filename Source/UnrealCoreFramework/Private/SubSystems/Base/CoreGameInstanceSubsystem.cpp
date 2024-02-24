// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/Base/CoreGameInstanceSubsystem.h"

DEFINE_LOG_CATEGORY(LogGameInstanceSubsystem);

void UCoreGameInstanceSubsystem::PreInitialize()
{
}

void UCoreGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	PreInitialize();

	Super::Initialize(Collection);
	UE_LOG(LogGameInstanceSubsystem, Log, TEXT("Initialize UCoreGameInstanceSubsystem"));

	PostInitialize();
}

void UCoreGameInstanceSubsystem::PostInitialize()
{
}

void UCoreGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogGameInstanceSubsystem, Log, TEXT("Deinitialize UCoreGameInstanceSubsystem"));
}

int32 UCoreGameInstanceSubsystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}