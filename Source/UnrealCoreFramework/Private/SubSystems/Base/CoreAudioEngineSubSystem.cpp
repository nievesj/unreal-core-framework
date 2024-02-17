// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/Base/CoreAudioEngineSubSystem.h"

DEFINE_LOG_CATEGORY(LogAudioSubsystem);

void UCoreAudioEngineSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogAudioSubsystem, Log, TEXT("Initialize UCoreAudioEngineSubSystem"));
}

void UCoreAudioEngineSubSystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogAudioSubsystem, Log, TEXT("Deinitialize UCoreAudioEngineSubSystem"));
}

int32 UCoreAudioEngineSubSystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}