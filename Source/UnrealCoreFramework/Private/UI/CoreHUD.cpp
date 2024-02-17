// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreHUD.h"

void ACoreHUD::ShowMainHUD()
{
	UE_LOG(LogTemp, Log, TEXT("ShowMainHUD"));

	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	MainBlade = CreateWidget<UCoreWidget>(PC, MainBladeClass);

	MainBlade->AddToViewport();
}

void ACoreHUD::HideMainHUD()
{
	if (MainBlade)
	{
		MainBlade->RemoveFromParent();
		MainBlade = nullptr;
	}
}
