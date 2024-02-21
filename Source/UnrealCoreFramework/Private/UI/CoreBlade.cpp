// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CoreBlade.h"

#include "Components/Button.h"
#include "SubSystems/LocalPlayer/UISubsystem.h"

void UCoreBlade::NativeConstruct()
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

void UCoreBlade::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCoreBlade::InternalShown()
{
	Super::InternalShown();

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UCoreBlade::Handle_OnExitButtonClicked);
	}
}

void UCoreBlade::InternalHidden()
{
	Super::InternalHidden();
	UISubsystem->RemoveBlade(this);
}

void UCoreBlade::Handle_OnExitButtonClicked()
{
	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveAll(this);
	}
	Close();
}

void UCoreBlade::Open()
{
	IBladeableWidgetInterface::Open();
	Show();
}

void UCoreBlade::Close()
{
	IBladeableWidgetInterface::Close();
	Hide();
}
