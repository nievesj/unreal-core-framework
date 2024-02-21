// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BladeableWidgetInterface.h"
#include "CoreMinimal.h"
#include "CoreWidget.h"

#include "CoreBlade.generated.h"

class UButton;
class UUISubsystem;

UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class UNREALCOREFRAMEWORK_API UCoreBlade : public UCoreWidget, public IBladeableWidgetInterface
{
public:
	virtual void Open() override;
	virtual void Close() override;

private:
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void InternalShown() override;
	virtual void InternalHidden() override;

	UFUNCTION()
	void Handle_OnExitButtonClicked();
	
	UPROPERTY(BlueprintReadWrite, Category = CoreBlade, meta = (BindWidgetOptional))
	UButton* ExitButton;

	UPROPERTY(Transient)
	UUISubsystem* UISubsystem;
};
