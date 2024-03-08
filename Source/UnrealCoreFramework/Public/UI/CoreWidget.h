// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CommonUserWidget.h"
#include "CoreMinimal.h"
#include "UiCoreFrameworkTypes.h"

#include "CoreWidget.generated.h"

class UCanvasPanel;
class UUISubsystem;

DECLARE_LOG_CATEGORY_EXTERN(LogCoreWidget, Log, All);

UCLASS(Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "Core Framework UI", DisableNativeTick))
class UNREALCOREFRAMEWORK_API UCoreWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UUISubsystem* GetUISubsystem();
	
	UFUNCTION(BlueprintCallable, Category = CoreWidget)
	void Show();

	UFUNCTION(BlueprintCallable, Category = CoreWidget)
	void Hide();

	UFUNCTION(BlueprintImplementableEvent, Category = CoreWidget)
	void OnShown();

	UFUNCTION(BlueprintImplementableEvent, Category = CoreWidget)
	void OnHidden();

protected:
	void PlayTweenTransition(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode);
	void PlayWidgetAnimation(UWidgetAnimation* Anim, const FWidgetAnimationOptions& WidgetAnimationOptions, const EWidgetTransitionMode WidgetTransitionMode);

	void Scale(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode);
	void Translation(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode);
	void Fade(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode);
	void GetViewportTranslationVectors(EWidgetTranslationType WidgetTranslationType, FVector2D& OutStart, FVector2D& OutEnd);
	void HandleOnWidgetAnimationCompleted(const EWidgetTransitionMode WidgetTransitionMode);
	
	virtual void InternalShown();
	virtual void InternalHidden();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget)
	EWidgetAnimationType WidgetAnimationType = EWidgetAnimationType::WidgetTween;

	UPROPERTY(BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetOptional))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetTween"))
	FWidgetTweenTransitionOptions TweenEntranceOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetTween"))
	FWidgetTweenTransitionOptions TweenExitOptions;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	UWidgetAnimation* WidgetAnimationIntro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	FWidgetAnimationOptions WidgetAnimationOptionsIntro;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	UWidgetAnimation* WidgetAnimationOuttro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	FWidgetAnimationOptions WidgetAnimationOptionsOuttro;
};
