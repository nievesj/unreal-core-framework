// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/LocalPlayer/UISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/UnrealCoreFrameworkSettings.h"
#include "UI/CoreHUD.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogUISubsystem);

UCoreWidget* UUISubsystem::CreatePage(APlayerController* Owner, TSubclassOf<UCoreWidget> PageClass)
{
	if (!Owner)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Owner is null"));
		return nullptr;
	}

	if (!IsValid(PageClass))
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("PageClass is not valid"));
		return nullptr;
	}

	if (const UClass* Class = PageClass.Get(); !Class->ImplementsInterface(UPageableWidgetInterface::StaticClass()))
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Parameter Page does not implement Interface UPageableWidgetInterface."));
		return nullptr;
	}

	if (UCoreWidget* Page = CreateWidget<UCoreWidget>(Owner, PageClass))
	{
		Page->AddToViewport();
		IPageableWidgetInterface* PageInt = Cast<IPageableWidgetInterface>(Page);

		CoreWidgetsOpen.Push(PageInt);
		PageInt->Open();
		UE_VLOG_UELOG(this, LogUISubsystem, Log, TEXT("Created Page %s"), *Page->GetName());
		return Page;
	}

	UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to create Page."));
	return nullptr;
}

void UUISubsystem::RemovePage(IPageableWidgetInterface* Page)
{
	if(Page)
	{
		if (UCoreWidget* Widget = Cast<UCoreWidget>(Page))
		{
			Widget->RemoveFromParent();
		}

		CoreWidgetsOpen.Remove(Page);
	}
}

void UUISubsystem::RemoveAllPages()
{
	for (IPageableWidgetInterface* Page : CoreWidgetsOpen)
	{
		Page->Close();
	}

	CoreWidgetsOpen.Empty();
}

IPageableWidgetInterface* UUISubsystem::GetTopPage()
{
	return CoreWidgetsOpen.Top();
}

void UUISubsystem::CreateMainPage(ECoreMainPageType MainPageType)
{
	const UUnrealCoreFrameworkSettings* Settings = UUnrealCoreFrameworkSettings::GetSettings();
	if (!Settings)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to get Developer Settings for UnrealCoreFrameworkSettings."));
		return;
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to get Player Controller."));
		return;
	}

	switch (MainPageType)
	{
		case ECoreMainPageType::MainMenu:
			if (MainMenuPage)
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Warning, TEXT("MainMenuPage is already open. Ignoring."));
			}
			else
			{
				if (MainHUDPage)
				{
					RemovePage(MainHUDPage);
					MainHUDPage = nullptr;
				}
				if (PauseMenuPage)
				{
					RemovePage(PauseMenuPage);
					PauseMenuPage = nullptr;
				}

				if (UCoreWidget* Page = CreatePage(PC, *Settings->MainMenuPage))
				{
					MainMenuPage = Cast<UCorePage>(Page);
				}
			}
			break;
		case ECoreMainPageType::MainHUD:
			if (MainMenuPage)
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Warning, TEXT("MainHUDPage is already open. Ignoring."));
			}
			else
			{
				if (UCoreWidget* Page = CreatePage(PC, Settings->MainHUDPage))
				{
					MainHUDPage = Cast<UCorePage>(Page);
				}
			}
			break;
		case ECoreMainPageType::PauseMenu:
			if (PauseMenuPage)
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Warning, TEXT("PauseMenuPage is already open. Ignoring."));
			}
			else
			{
				if (UCoreWidget* Page = CreatePage(PC, Settings->PauseMenuPage))
				{
					PauseMenuPage = Cast<UCorePage>(Page);
				}
			}
			break;
	}
}

void UUISubsystem::RemoveMainPage(ECoreMainPageType MainPageType)
{
	switch (MainPageType)
	{
		case ECoreMainPageType::MainMenu:
			if (MainMenuPage)
			{
				RemovePage(MainMenuPage);
				MainMenuPage = nullptr;
			}
			break;
		case ECoreMainPageType::MainHUD:
			if (MainHUDPage)
			{
				RemovePage(MainHUDPage);
				MainHUDPage = nullptr;
			}
			break;
		case ECoreMainPageType::PauseMenu:
			if (PauseMenuPage)
			{
				RemovePage(PauseMenuPage);
				PauseMenuPage = nullptr;
			}
			break;
	}
}

UCorePage* UUISubsystem::GetMainPage(ECoreMainPageType MainPageType)
{
	switch (MainPageType)
	{
		case ECoreMainPageType::MainMenu:
			return MainMenuPage;
			break;
		case ECoreMainPageType::MainHUD:
			return MainHUDPage;
			break;
		case ECoreMainPageType::PauseMenu:
			return PauseMenuPage;
			break;
	}

	return nullptr;
}

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_VLOG_UELOG(this, LogUISubsystem, Log, TEXT("Initializing UI Subsystem"));
}

void UUISubsystem::Deinitialize()
{
	UE_LOG(LogUISubsystem, Warning, TEXT("Deinitializing UI Subsystem"))
}
