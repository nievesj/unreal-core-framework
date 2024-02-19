// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "UiCoreFrameworkTypes.h"

#include "CoreWidget.generated.h"

class UCanvasPanel;

UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class UNREALCOREFRAMEWORK_API UCoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
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
	void Move(FVector2D Start, FVector2D End, const EWidgetTransitionMode WidgetTransitionMode);
	void Fade(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode);

	void HandleOnWidgetAnimationCompleted(const EWidgetTransitionMode WidgetTransitionMode);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget)
	EWidgetAnimationType WidgetAnimationType = EWidgetAnimationType::WidgetTween;

	UPROPERTY(BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetTween"))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetTween"))
	FWidgetTweenTransitionOptions WidgetTweenTransitionOptionsIntro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetTween"))
	FWidgetTweenTransitionOptions WidgetTweenTransitionOptionsOuttro;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	UWidgetAnimation* WidgetAnimationIntro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	FWidgetAnimationOptions WidgetAnimationOptionsIntro;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	UWidgetAnimation* WidgetAnimationOuttro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreWidget, meta = (BindWidgetAnimOptional, EditCondition = "WidgetAnimationType == EWidgetAnimationType::WidgetAnimation"))
	FWidgetAnimationOptions WidgetAnimationOptionsOuttro;
};
