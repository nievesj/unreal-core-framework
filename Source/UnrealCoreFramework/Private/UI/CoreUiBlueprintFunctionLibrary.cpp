// MIT License. Copyright (c) 2024  José M. Nieves

#include "UI/CoreUiBlueprintFunctionLibrary.h"

#include "SubSystems/LocalPlayer/UISubsystem.h"
#include "UI/CoreWidget.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogCoreUiFunctionLibrary);

UCoreWidget* UCoreUiBlueprintFunctionLibrary::CreateBlade(UCoreWidget* Widget, TSubclassOf<UCoreWidget> BladeClass)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::CreateBlade - Widget is invalid"));
	}

	APlayerController* PC = Widget->GetOwningPlayer();
	if (!PC)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::CreateBlade - Failed to get Player Controller"));
	}

	UUISubsystem* UISubsystem = Widget->GetUISubsystem();
	if (!UISubsystem)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::CreateBlade - Failed to get UISubsystem"));
	}

	return UISubsystem->CreateBlade(PC, BladeClass);
}

void UCoreUiBlueprintFunctionLibrary::RemoveBlade(UCoreWidget* Widget, UCoreBlade* Blade)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveBlade - Widget is invalid"));
	}

	if (UUISubsystem* UISubsystem = Widget->GetUISubsystem())
	{
		UISubsystem->RemoveBlade(Cast<IBladeableWidgetInterface>(Blade));
	}
}

void UCoreUiBlueprintFunctionLibrary::CreateMainBlade(UCoreWidget* Widget, ECoreMainBladeType MainBladeType)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveBlade - Widget is invalid"));
	}

	if (UUISubsystem* UISubsystem = Widget->GetUISubsystem())
	{
		UISubsystem->CreateMainBlade(MainBladeType);
	}
}

void UCoreUiBlueprintFunctionLibrary::RemoveMainBlade(UCoreWidget* Widget, ECoreMainBladeType MainBladeType)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveMainBlade - Widget is invalid"));
	}

	if (UUISubsystem* UISubsystem = Widget->GetUISubsystem())
	{
		UISubsystem->RemoveMainBlade(MainBladeType);
	}
}

UCoreBlade* UCoreUiBlueprintFunctionLibrary::GetMainBlade(UCoreWidget* Widget, ECoreMainBladeType MainBladeType)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::GetMainBlade - Widget is invalid"));
		return nullptr;
	}

	UUISubsystem* UISubsystem = Widget->GetUISubsystem();
	if (!UISubsystem)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::GetMainBlade - Failed to get UISubsystem"));
		return nullptr;
	}

	return UISubsystem->GetMainBlade(MainBladeType);
}
