// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreBlade.h"
#include "SubSystems/LocalPlayer/UISubsystem.h"

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

void UCoreBlade::NativeConstruct()
{
	Super::NativeConstruct();

	if(const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if(const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			UISubsystem = LocalPlayer->GetSubsystem<UUISubsystem>();
		}
	}
}
