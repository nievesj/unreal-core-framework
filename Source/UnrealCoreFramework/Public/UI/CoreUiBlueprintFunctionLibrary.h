// MIT License. Copyright (c) 2024  José M. Nieves

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CoreUiBlueprintFunctionLibrary.generated.h"

class UCoreBlade;
DECLARE_LOG_CATEGORY_EXTERN(LogCoreUiFunctionLibrary, Log, All);

class UCoreWidget;
/**
 Blueprint library for the Core Framework UI System
 */
UCLASS(meta = (ScriptName = "CoreUiFunctionLibrary"))
class UNREALCOREFRAMEWORK_API UCoreUiBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static UCoreWidget* CreateBlade(UCoreWidget* Widget, TSubclassOf<UCoreWidget> BladeClass);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void RemoveBlade(UCoreWidget* Widget, UCoreBlade* Blade);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void CreateMainBlade(UCoreWidget* Widget, ECoreMainBladeType MainBladeType);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static void RemoveMainBlade(UCoreWidget* Widget, ECoreMainBladeType MainBladeType);

	UFUNCTION(BlueprintCallable, Category = CoreFrameworkUi, Meta = (DefaultToSelf = "Widget"))
	static UCoreBlade* GetMainBlade(UCoreWidget* Widget, ECoreMainBladeType MainBladeType);

	
};
