// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreWidget.h"
#include "GameFramework/HUD.h"
#include "CoreHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOREFRAMEWORK_API ACoreHUD : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = UnrealCoreFrameworkSettings)
	void ShowMainHUD();
	
	UFUNCTION(BlueprintCallable, Category = UnrealCoreFrameworkSettings)
	void HideMainHUD();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnrealCoreFrameworkSettings, Meta = (DisplayName = "Main HUD Class"))
	TSubclassOf<UCoreWidget> MainBladeClass;

	UPROPERTY(Transient)
	UCoreWidget* MainBlade;
};
