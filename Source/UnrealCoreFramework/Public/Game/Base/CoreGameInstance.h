// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CoreGameInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCoreGameInstance, Log, All);

UCLASS()
class UNREALCOREFRAMEWORK_API UCoreGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UCoreGameInstance();
	virtual class AGameModeBase* CreateGameModeForURL(FURL InURL, UWorld* InWorld);

	virtual void Init() override;
	virtual void OnStart() override;
	virtual void FinishDestroy() override;
	virtual void Shutdown() override;

	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;

protected:
	void OnLocalPlayerAdded(ULocalPlayer* LocalPlayer);
};