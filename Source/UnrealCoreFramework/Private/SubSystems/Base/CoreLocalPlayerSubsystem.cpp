// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/Base/CoreLocalPlayerSubsystem.h"

DEFINE_LOG_CATEGORY(LogLocalPlayerSubsystem);

void UCoreLocalPlayerSubsystem::PreInitialize()
{
}

void UCoreLocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogLocalPlayerSubsystem, Log, TEXT("Initialize UCoreLocalPlayerSubsystem"));
}

void UCoreLocalPlayerSubsystem::PostInitialize()
{
}

void UCoreLocalPlayerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogLocalPlayerSubsystem, Log, TEXT("Deinitialize UCoreLocalPlayerSubsystem"));
}

int32 UCoreLocalPlayerSubsystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}
