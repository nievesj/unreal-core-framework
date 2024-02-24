// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubSystems/Base/CoreLocalPlayerSubsystem.h"

#include "InputSubsystem.generated.h"

/**
 *
 */
UCLASS()
class UNREALCOREFRAMEWORK_API UInputSubsystem : public UCoreLocalPlayerSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
