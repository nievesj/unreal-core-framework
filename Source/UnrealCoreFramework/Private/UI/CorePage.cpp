// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CorePage.h"

#include "Components/Button.h"
#include "SubSystems/LocalPlayer/UISubsystem.h"

void UCorePage::NativeConstruct()
{
	Super::NativeConstruct();

	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			UISubsystem = LocalPlayer->GetSubsystem<UUISubsystem>();
		}
	}
}

void UCorePage::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCorePage::InternalShown()
{
	Super::InternalShown();

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UCorePage::Handle_OnExitButtonClicked);
	}
}

void UCorePage::InternalHidden()
{
	Super::InternalHidden();
	UISubsystem->RemovePage(this);
}

void UCorePage::Handle_OnExitButtonClicked()
{
	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveAll(this);
	}
	Close();
}

void UCorePage::Open()
{
	IPageableWidgetInterface::Open();
	DisablePlayerControllerInput = DisablePlayerInput;
	Show();
}

void UCorePage::Close()
{
	IPageableWidgetInterface::Close();
	Hide();
}
