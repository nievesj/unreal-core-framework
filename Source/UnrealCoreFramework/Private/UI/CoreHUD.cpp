// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CoreHUD.h"

void ACoreHUD::ShowMainHUD()
{
	UE_LOG(LogTemp, Log, TEXT("ShowMainHUD"));

	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	MainPage = CreateWidget<UCoreWidget>(PC, MainPageClass);

	MainPage->AddToViewport();
}

void ACoreHUD::HideMainHUD()
{
	if (MainPage)
	{
		MainPage->RemoveFromParent();
		MainPage = nullptr;
	}
}
