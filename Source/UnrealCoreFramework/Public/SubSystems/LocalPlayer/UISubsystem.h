// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubSystems/Base/CoreLocalPlayerSubsystem.h"
#include "UI/BladeableWidgetInterface.h"

#include "UISubsystem.generated.h"

class UCoreBlade;
class ACorePlayerController;
class UCoreWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogUISubsystem, Log, All);

UENUM(BlueprintType)
enum class ECoreMainBladeType : uint8
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
	UCoreWidget* CreateBlade(APlayerController* Owner, TSubclassOf<UCoreWidget> BladeClass);
	void RemoveBlade(IBladeableWidgetInterface* Blade);
	void RemoveAllBlades();
	IBladeableWidgetInterface* GetTopBlade();

	void CreateMainBlade(ECoreMainBladeType MainBladeType);
	void RemoveMainBlade(ECoreMainBladeType MainBladeType);
	UCoreBlade* GetMainBlade(ECoreMainBladeType MainBladeType);

private:
	UPROPERTY(Transient)
	TArray<IBladeableWidgetInterface*> CoreWidgetsOpen;
	
	UPROPERTY(Transient)
	UCoreBlade* MainMenuBlade;

	UPROPERTY(Transient)
	UCoreBlade* MainHUDBlade;

	UPROPERTY(Transient)
	UCoreBlade* PauseMenuBlade;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
