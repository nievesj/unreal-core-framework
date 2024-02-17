// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/Async/AsyncManagerSubSystem.h"

void UAsyncManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TickHandler = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UAsyncManagerSubSystem::Tick));
}

bool UAsyncManagerSubSystem::Tick(float DeltaSeconds)
{
	//Add an array of tasks, then iterate
	return true;
}

void UAsyncManagerSubSystem::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandler);
	Super::Deinitialize();
}
