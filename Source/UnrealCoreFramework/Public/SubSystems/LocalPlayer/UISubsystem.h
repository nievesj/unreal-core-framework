﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubSystems/Base/CoreLocalPlayerSubsystem.h"
#include "UI/PageableWidgetInterface.h"

#include "UISubsystem.generated.h"

class UCorePage;
class ACorePlayerController;
class UCoreWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogUISubsystem, Log, All);

UENUM(BlueprintType)
enum class ECoreMainPageType : uint8
{
	MainMenu,
	MainHUD,
	PauseMenu
};

UCLASS()
class UNREALCOREFRAMEWORK_API UUISubsystem : public UCoreLocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UCoreWidget* CreatePage(APlayerController* Owner, TSubclassOf<UCoreWidget> PageClass);
	void RemovePage(IPageableWidgetInterface* Page);
	void RemoveAllPages();
	
	IPageableWidgetInterface* GetTopPage();
	void CreateMainPage(ECoreMainPageType MainPageType);
	UCoreWidget* GetMainPage(ECoreMainPageType MainPageType);

	bool ShouldDisablePlayerControllerInput();
	void SetPlayerControllerInput(APlayerController* PC, bool IsDisabled);

private:
	UPROPERTY(Transient)
	TArray<IPageableWidgetInterface*> CoreWidgetsOpen;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
