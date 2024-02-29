﻿// MIT License. Copyright (c) 2024  José M. Nieves

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CoreUiBlueprintFunctionLibrary.generated.h"

class UCorePage;
class UCoreWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogCoreUiFunctionLibrary, Log, All);

/**
 Blueprint library for the Core Framework UI System
 */
UCLASS(meta = (ScriptName = "CoreUiFunctionLibrary"))
class UNREALCOREFRAMEWORK_API UCoreUiBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static UCoreWidget* CreatePage(UCoreWidget* Widget, TSubclassOf<UCoreWidget> PageClass);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void RemovePage(UCoreWidget* Widget, UCorePage* Page);
	
	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void CreateMainHUD(UCoreWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void CreateMainMenu(UCoreWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void CreatePauseMenu(UCoreWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static bool GetMainPage(UCoreWidget* Widget, ECoreMainPageType CoreMainPageType, UCoreWidget*& OutCoreWidget);
};
