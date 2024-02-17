// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CoreWidget.generated.h"

class UCanvasPanel;

UENUM(BlueprintType)
enum class EWidgetTransitionType : uint8
{
	NotUsed,
	Scale,
	Left,
	Right,
	Top,
	Bottom,
	Fade
};

UENUM(BlueprintType)
enum class EWidgetTransitionMode : uint8
{
	Intro,
	Outtro,
};

UENUM(BlueprintType)
enum class EWidgetAnimationType : uint8
{
	None,
	WidgetTween,
	WidgetAnimation,
};

USTRUCT(BlueprintType)
struct FWidgetTweenTransitionOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	EWidgetTransitionType TransitionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	float TransitionTime = 0.5f;
};

USTRUCT(BlueprintType)
struct FWidgetAnimationOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	float StartAtTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	int32 NumberOfLoops = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	float PlaybackSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	bool bRestoreState = false;
};


UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta=( DontUseGenericSpawnObject="True", DisableNativeTick))
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
	
	void Scale(FVector2D Start, FVector2D End, const EWidgetTransitionMode WidgetTransitionMode);
	void Move(FVector2D Start, FVector2D End, const EWidgetTransitionMode WidgetTransitionMode);
	void Fade(const EWidgetTransitionMode WidgetTransitionMode);

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
