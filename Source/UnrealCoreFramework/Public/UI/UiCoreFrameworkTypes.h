// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "UiCoreFrameworkTypes.generated.h"

enum class EBUIEasingType;
namespace EUMGSequencePlayMode
{
enum Type : int;
}

UENUM(BlueprintType)
enum class EWidgetTransitionType : uint8
{
	NotUsed,
	Scale,
	Translation,
	Fade
};

UENUM(BlueprintType)
enum class EWidgetTranslationType : uint8
{
	FromLeft,
	FromRight,
	FromTop,
	FromBottom,
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
	EWidgetTranslationType WidgetTranslationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	EBUIEasingType EasingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	float TransitionTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Fade"))
	float FadeMaxVisibility = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Fade"))
	float FadeMinVisibility = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Scale"))
	FVector2D MaxScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Scale"))
	FVector2D MinScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Translation"))
	bool UseViewportAsTranslationOrigin = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "UseViewportAsTranslationOrigin == false && TransitionType == EWidgetTransitionType::Translation"))
	FVector2D StartTranslationVector2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "UseViewportAsTranslationOrigin == false && TransitionType == EWidgetTransitionType::Translation"))
	FVector2D EndTranslationVector2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Translation"))
	FVector2D StartTranslationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions, meta = (EditCondition = "TransitionType == EWidgetTransitionType::Translation"))
	FVector2D EndTranslationOffset;
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