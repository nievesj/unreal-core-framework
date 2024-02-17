// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreWidget.h"
#include "BladeableWidgetInterface.h"
#include "CoreBlade.generated.h"

class UUISubsystem;

UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta=( DontUseGenericSpawnObject="True", DisableNativeTick))
class UNREALCOREFRAMEWORK_API UCoreBlade : public UCoreWidget, public IBladeableWidgetInterface
{
public:
	virtual void Open() override;
	virtual void Close() override;

private:
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Transient)
	UUISubsystem* UISubsystem;
};
