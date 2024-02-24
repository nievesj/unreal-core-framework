// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/Base/CoreEditorSubsystem.h"

DEFINE_LOG_CATEGORY(LogEditorSubsystem);

void UCoreEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogEditorSubsystem, Log, TEXT("Initialize UCoreEditorSubsystem"));
}

void UCoreEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogEditorSubsystem, Log, TEXT("Deinitialize UCoreEditorSubsystem"));
}

int32 UCoreEditorSubsystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}
