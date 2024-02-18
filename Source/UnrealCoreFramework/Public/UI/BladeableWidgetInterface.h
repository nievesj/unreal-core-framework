// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "BladeableWidgetInterface.generated.h"

/**
 *
 */
UINTERFACE(MinimalAPI)
class UBladeableWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREALCOREFRAMEWORK_API IBladeableWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void Open();
	virtual void Close();
};