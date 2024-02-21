// Fill out your copyright notice in the Description page of Project Settings.

#include "SubSystems/LocalPlayer/UISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/UnrealCoreFrameworkSettings.h"
#include "UI/CoreHUD.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogUISubsystem);

UCoreWidget* UUISubsystem::CreateBlade(APlayerController* Owner, TSubclassOf<UCoreWidget> BladeClass)
{
	if (!Owner)
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Owner is null"));
		return nullptr;
	}

	if (!IsValid(BladeClass))
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("BladeClass is not valid"));
		return nullptr;
	}

	if (const UClass* Class = BladeClass.Get(); !Class->ImplementsInterface(UBladeableWidgetInterface::StaticClass()))
	{
		UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Parameter Blade does not implement Interface UBladeableWidgetInterface."));
		return nullptr;
	}

	if (UCoreWidget* Blade = CreateWidget<UCoreWidget>(Owner, BladeClass))
	{
		Blade->AddToViewport();
		IBladeableWidgetInterface* BladeInt = Cast<IBladeableWidgetInterface>(Blade);

		CoreWidgetsOpen.Push(BladeInt);
		BladeInt->Open();
		UE_VLOG_UELOG(this, LogUISubsystem, Log, TEXT("Created Blade %s"), *Blade->GetName());
		return Blade;
	}

	UE_VLOG_UELOG(this, LogUISubsystem, Error, TEXT("Failed to create Blade."));
	return nullptr;
}

void UUISubsystem::RemoveBlade(IBladeableWidgetInterface* Blade)
{
	if(Blade)
	{
		if (UCoreWidget* Widget = Cast<UCoreWidget>(Blade))
		{
			Widget->RemoveFromParent();
		}

		CoreWidgetsOpen.Remove(Blade);
	}
}

void UUISubsystem::RemoveAllBlades()
{
	for (IBladeableWidgetInterface* Blade : CoreWidgetsOpen)
	{
		Blade->Close();
	}

	CoreWidgetsOpen.Empty();
}

IBladeableWidgetInterface* UUISubsystem::GetTopBlade()
{
	return CoreWidgetsOpen.Top();
}

void UUISubsystem::CreateMainBlade(ECoreMainBladeType MainBladeType)
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

	switch (MainBladeType)
	{
		case ECoreMainBladeType::MainMenu:
			if (MainMenuBlade)
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Warning, TEXT("MainMenuBlade is already open. Ignoring."));
			}
			else
			{
				if (MainHUDBlade)
				{
					RemoveBlade(MainHUDBlade);
					MainHUDBlade = nullptr;
				}
				if (PauseMenuBlade)
				{
					RemoveBlade(PauseMenuBlade);
					PauseMenuBlade = nullptr;
				}

				if (UCoreWidget* Blade = CreateBlade(PC, *Settings->MainMenuBlade))
				{
					MainMenuBlade = Cast<UCoreBlade>(Blade);
				}
			}
			break;
		case ECoreMainBladeType::MainHUD:
			if (MainMenuBlade)
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Warning, TEXT("MainHUDBlade is already open. Ignoring."));
			}
			else
			{
				if (UCoreWidget* Blade = CreateBlade(PC, Settings->MainHUDBlade))
				{
					MainHUDBlade = Cast<UCoreBlade>(Blade);
				}
			}
			break;
		case ECoreMainBladeType::PauseMenu:
			if (PauseMenuBlade)
			{
				UE_VLOG_UELOG(this, LogUISubsystem, Warning, TEXT("PauseMenuBlade is already open. Ignoring."));
			}
			else
			{
				if (UCoreWidget* Blade = CreateBlade(PC, Settings->PauseMenuBlade))
				{
					PauseMenuBlade = Cast<UCoreBlade>(Blade);
				}
			}
			break;
	}
}

void UUISubsystem::RemoveMainBlade(ECoreMainBladeType MainBladeType)
{
	switch (MainBladeType)
	{
		case ECoreMainBladeType::MainMenu:
			if (MainMenuBlade)
			{
				RemoveBlade(MainMenuBlade);
				MainMenuBlade = nullptr;
			}
			break;
		case ECoreMainBladeType::MainHUD:
			if (MainHUDBlade)
			{
				RemoveBlade(MainHUDBlade);
				MainHUDBlade = nullptr;
			}
			break;
		case ECoreMainBladeType::PauseMenu:
			if (PauseMenuBlade)
			{
				RemoveBlade(PauseMenuBlade);
				PauseMenuBlade = nullptr;
			}
			break;
	}
}

UCoreBlade* UUISubsystem::GetMainBlade(ECoreMainBladeType MainBladeType)
{
	switch (MainBladeType)
	{
		case ECoreMainBladeType::MainMenu:
			return MainMenuBlade;
			break;
		case ECoreMainBladeType::MainHUD:
			return MainHUDBlade;
			break;
		case ECoreMainBladeType::PauseMenu:
			return PauseMenuBlade;
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
