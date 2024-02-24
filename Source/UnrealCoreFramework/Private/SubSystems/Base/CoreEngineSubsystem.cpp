// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/Base/CoreEngineSubsystem.h"

DEFINE_LOG_CATEGORY(LogEngineSubsystem);

void UCoreEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogEngineSubsystem, Log, TEXT("Initialize UCoreEngineSubsystem"));
}

void UCoreEngineSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UE_LOG(LogEngineSubsystem, Log, TEXT("De Deinitialize UCoreEngineSubsystem"));
}

int32 UCoreEngineSubsystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}
