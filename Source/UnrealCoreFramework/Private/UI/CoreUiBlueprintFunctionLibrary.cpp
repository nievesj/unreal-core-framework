// MIT License. Copyright (c) 2024  José M. Nieves

#include "UI/CoreUiBlueprintFunctionLibrary.h"

#include "SubSystems/LocalPlayer/UISubsystem.h"
#include "UI/CoreWidget.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogCoreUiFunctionLibrary);

UCoreWidget* UCoreUiBlueprintFunctionLibrary::CreatePage(UCoreWidget* Widget, TSubclassOf<UCoreWidget> PageClass)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::CreatePage - Widget is invalid"));
	}

	APlayerController* PC = Widget->GetOwningPlayer();
	if (!PC)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::CreatePage - Failed to get Player Controller"));
	}

	UUISubsystem* UISubsystem = Widget->GetUISubsystem();
	if (!UISubsystem)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::CreatePage - Failed to get UISubsystem"));
	}

	return UISubsystem->CreatePage(PC, PageClass);
}

void UCoreUiBlueprintFunctionLibrary::RemovePage(UCoreWidget* Widget, UCorePage* Page)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemovePage - Widget is invalid"));
	}

	if (UUISubsystem* UISubsystem = Widget->GetUISubsystem())
	{
		UISubsystem->RemovePage(Cast<IPageableWidgetInterface>(Page));
	}
}

void UCoreUiBlueprintFunctionLibrary::CreateMainPage(UCoreWidget* Widget, ECoreMainPageType MainPageType)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemovePage - Widget is invalid"));
	}

	if (UUISubsystem* UISubsystem = Widget->GetUISubsystem())
	{
		UISubsystem->CreateMainPage(MainPageType);
	}
}

void UCoreUiBlueprintFunctionLibrary::RemoveMainPage(UCoreWidget* Widget, ECoreMainPageType MainPageType)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveMainPage - Widget is invalid"));
	}

	if (UUISubsystem* UISubsystem = Widget->GetUISubsystem())
	{
		UISubsystem->RemoveMainPage(MainPageType);
	}
}

UCorePage* UCoreUiBlueprintFunctionLibrary::GetMainPage(UCoreWidget* Widget, ECoreMainPageType MainPageType)
{
	if (!Widget)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::GetMainPage - Widget is invalid"));
		return nullptr;
	}

	UUISubsystem* UISubsystem = Widget->GetUISubsystem();
	if (!UISubsystem)
	{
		UE_VLOG_UELOG(Widget, LogCoreUiFunctionLibrary, Error, TEXT("UCoreUiBlueprintFunctionLibrary::GetMainPage - Failed to get UISubsystem"));
		return nullptr;
	}

	return UISubsystem->GetMainPage(MainPageType);
}
