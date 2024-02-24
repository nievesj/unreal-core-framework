// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/LocalPlayer/UISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
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
	if (Page)
	{
		CoreWidgetsOpen.Remove(Page);
		if (UCoreWidget* Widget = Cast<UCoreWidget>(Page))
		{
			if (APlayerController* PC = Widget->GetOwningPlayer())
			{
				SetPlayerControllerInput(PC, ShouldDisablePlayerControllerInput());
			}

			Widget->RemoveFromParent();
		}
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

	const UWorld* World = GetWorld();
	if (!World)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to get World."));
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to get Player Controller."));
		return;
	}

	switch (MainPageType)
	{
		case ECoreMainPageType::MainMenu:
			CreatePage(PC, *Settings->MainMenuPage);
			break;
		case ECoreMainPageType::MainHUD:
			CreatePage(PC, Settings->MainHUDPage);
			break;
		case ECoreMainPageType::PauseMenu:
			CreatePage(PC, Settings->PauseMenuPage);
			break;
	}

	SetPlayerControllerInput(PC, ShouldDisablePlayerControllerInput());
}

UCoreWidget* UUISubsystem::GetMainPage(ECoreMainPageType MainPageType)
{
	TSubclassOf<UCorePage> MainClass = nullptr;
	const UUnrealCoreFrameworkSettings* Settings = UUnrealCoreFrameworkSettings::GetSettings();
	if (!Settings)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to get Developer Settings for UnrealCoreFrameworkSettings."));
		return nullptr;
	}

	switch (MainPageType)
	{
		case ECoreMainPageType::MainMenu:
			MainClass = Settings->MainMenuPage;
			break;
		case ECoreMainPageType::MainHUD:
			MainClass = Settings->MainHUDPage;
			break;
		case ECoreMainPageType::PauseMenu:
			MainClass = Settings->PauseMenuPage;
			break;
	}
	
	UClass* Class = MainClass.Get();
	for (IPageableWidgetInterface* Int : CoreWidgetsOpen)
	{
		if (UCoreWidget* Widget = Cast<UCoreWidget>(Int))
		{
			if (Class && Widget->IsA(Class))
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Log, TEXT("Found %s"), *Widget->GetName());
				return Widget;
			}
		}
	}

	return nullptr;
}

bool UUISubsystem::ShouldDisablePlayerControllerInput()
{
	if (CoreWidgetsOpen.IsEmpty())
	{
		return false;
	}

	for (const IPageableWidgetInterface* Page : CoreWidgetsOpen)
	{
		if (Page->DisablePlayerControllerInput)
		{
			return true;
		}
	}

	return false;
}

void UUISubsystem::SetPlayerControllerInput(APlayerController* PC, bool IsDisabled)
{
	if (!PC)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Player Controller is invalid"));
		return;
	}

	ACharacter* Character = PC->GetCharacter();
	if (!Character)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Character is invalid"));
		return;
	}

	IsDisabled ? Character->DisableInput(PC) : Character->EnableInput(PC);
}

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_VLOG_UELOG(this, LogUISubsystem, Log, TEXT("Initializing UI Subsystem"));
}

void UUISubsystem::Deinitialize()
{
	UE_LOG(LogUISubsystem, Warning, TEXT("Deinitializing UI Subsystem"))
}
