﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UI/CoreWidget.h"

#include "Animation/UMGSequencePlayer.h"
#include "BUITween.h"
#include "Components/CanvasPanel.h"
#include "Components/Viewport.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogCoreWidget);

UUISubsystem* UCoreWidget::GetUISubsystem()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		UE_VLOG_UELOG(this, LogCoreWidget, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveMainPage - Failed to get Player Controller"));
		return nullptr;
	}

	const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_VLOG_UELOG(this, LogCoreWidget, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveMainPage - Failed to get Local Player"));
		return nullptr;
	}

	UUISubsystem* UISubsystem = LocalPlayer->GetSubsystem<UUISubsystem>();
	if (!UISubsystem)
	{
		UE_VLOG_UELOG(this, LogCoreWidget, Error, TEXT("UCoreUiBlueprintFunctionLibrary::RemoveMainPage - Failed to get UISubsystem"));
		return nullptr;
	}
	
	return UISubsystem;
}

void UCoreWidget::Show()
{
	switch (WidgetAnimationType)
	{
		case EWidgetAnimationType::WidgetTween:
			if (CanvasPanel)
			{
				PlayTweenTransition(TweenEntranceOptions, EWidgetTransitionMode::Intro);
			}
			break;
		case EWidgetAnimationType::WidgetAnimation:
			if (WidgetAnimationIntro)
			{
				PlayWidgetAnimation(WidgetAnimationIntro, WidgetAnimationOptionsIntro, EWidgetTransitionMode::Intro);
			}
			break;
	}
}

void UCoreWidget::Hide()
{
	switch (WidgetAnimationType)
	{
		case EWidgetAnimationType::WidgetTween:
			if (CanvasPanel)
			{
				PlayTweenTransition(TweenExitOptions, EWidgetTransitionMode::Outtro);
			}
			break;
		case EWidgetAnimationType::WidgetAnimation:
			if (WidgetAnimationOuttro)
			{
				PlayWidgetAnimation(WidgetAnimationOuttro, WidgetAnimationOptionsOuttro, EWidgetTransitionMode::Outtro);
			}
			break;
	}
}

void UCoreWidget::PlayWidgetAnimation(UWidgetAnimation* Anim, const FWidgetAnimationOptions& WidgetAnimationOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	UUMGSequencePlayer* Player = GetOrAddSequencePlayer(Anim);
	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	Player->OnSequenceFinishedPlaying().AddLambda(
		[WidgetTransitionMode, WeakThis](UUMGSequencePlayer& Player)
		{
			if (UCoreWidget* Widget = WeakThis.Get())
			{
				Widget->HandleOnWidgetAnimationCompleted(WidgetTransitionMode);
			}
		}
	);

	PlayAnimation(Anim, WidgetAnimationOptions.StartAtTime, WidgetAnimationOptions.NumberOfLoops, WidgetAnimationOptions.PlayMode, WidgetAnimationOptions.PlaybackSpeed);
}

void UCoreWidget::HandleOnWidgetAnimationCompleted(const EWidgetTransitionMode WidgetTransitionMode)
{
	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			InternalShown();
			break;
		case EWidgetTransitionMode::Outtro:
			InternalHidden();
			break;
	}
}
void UCoreWidget::InternalShown()
{
	OnShown();
}

void UCoreWidget::InternalHidden()
{
	OnHidden();
}

void UCoreWidget::PlayTweenTransition(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	switch (TweenTransitionOptions.TransitionType)
	{
		case EWidgetTransitionType::NotUsed:
			break;
		case EWidgetTransitionType::Scale:
			Scale(TweenTransitionOptions, WidgetTransitionMode);
			break;
		case EWidgetTransitionType::Translation:
			Translation(TweenTransitionOptions, WidgetTransitionMode);
			break;
		case EWidgetTransitionType::Fade:
			Fade(TweenTransitionOptions, WidgetTransitionMode);
			break;
	}
}

void UCoreWidget::GetViewportTranslationVectors(EWidgetTranslationType WidgetTranslationType, FVector2D& OutStart, FVector2D& OutEnd)
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	switch (WidgetTranslationType)
	{
		case EWidgetTranslationType::FromLeft:
			OutStart = FVector2D(ViewportSize.X, 0);
			OutEnd = FVector2D(0);
			break;
		case EWidgetTranslationType::FromRight:
			OutStart = FVector2D(-ViewportSize.X, 0);
			OutEnd = FVector2D(0);
			break;
		case EWidgetTranslationType::FromTop:
			OutStart = FVector2D(0, -ViewportSize.Y);
			OutEnd = FVector2D(0);
			break;
		case EWidgetTranslationType::FromBottom:
			OutStart = FVector2D(0, ViewportSize.Y);
			OutEnd = FVector2D(0);
			break;
	}
}

void UCoreWidget::Scale(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	FVector2D Start;
	FVector2D End;
	float StartOpacity = 1;
	float EndOpacity = 1;
	float Duration = 0;
	EBUIEasingType EasingType = EBUIEasingType::Linear;

	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			Start = TweenTransitionOptions.ScaleFrom;
			End = TweenTransitionOptions.ScaleTo;
			Duration = TweenTransitionOptions.TransitionTime;
			EasingType = TweenTransitionOptions.EasingType;
			StartOpacity = TweenTransitionOptions.FadeFrom;
			EndOpacity = TweenTransitionOptions.FadeTo;
			break;
		case EWidgetTransitionMode::Outtro:
			Start = TweenTransitionOptions.ScaleFrom;
			End = TweenTransitionOptions.ScaleTo;
			Duration = TweenTransitionOptions.TransitionTime;
			EasingType = TweenTransitionOptions.EasingType;
			StartOpacity = TweenTransitionOptions.FadeFrom;
			EndOpacity = TweenTransitionOptions.FadeTo;
			break;
	}

	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	UBUITween::Create(this, Duration)
		.FromScale(Start)
		.ToScale(End)
		.FromOpacity(StartOpacity)
		.ToOpacity(EndOpacity)
		.Easing(EasingType)
		.OnComplete(FBUITweenSignature::CreateLambda(
			[WidgetTransitionMode, WeakThis](UWidget* Owner)
			{
				if (UCoreWidget* Widget = WeakThis.Get())
				{
					Widget->HandleOnWidgetAnimationCompleted(WidgetTransitionMode);
				}
			}
		))
		.Begin();
}

void UCoreWidget::Translation(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	FVector2D Start;
	FVector2D End;
	float StartOpacity = 1;
	float EndOpacity = 1;
	float Duration = 0;
	EBUIEasingType EasingType = EBUIEasingType::Linear;

	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			if (!TweenTransitionOptions.UseViewportAsTranslationOrigin)
			{
				Start = TweenTransitionOptions.TranslationFrom + TweenTransitionOptions.TranslationFromOffset;
				End = TweenTransitionOptions.TranslationTo + TweenTransitionOptions.TranslationToOffset;
			}
			else
			{
				GetViewportTranslationVectors(TweenTransitionOptions.WidgetTranslationType, Start, End);
				Start += TweenTransitionOptions.TranslationFromOffset;
				End += TweenTransitionOptions.TranslationToOffset;
			}

			StartOpacity = TweenTransitionOptions.FadeFrom;
			EndOpacity = TweenTransitionOptions.FadeTo;
			Duration = TweenTransitionOptions.TransitionTime;
			EasingType = TweenTransitionOptions.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			if (!TweenTransitionOptions.UseViewportAsTranslationOrigin)
			{
				Start = TweenTransitionOptions.TranslationFrom + TweenTransitionOptions.TranslationFromOffset;
				End = TweenTransitionOptions.TranslationTo + TweenTransitionOptions.TranslationToOffset;
			}
			else
			{
				GetViewportTranslationVectors(TweenTransitionOptions.WidgetTranslationType, End, Start);
				Start += TweenTransitionOptions.TranslationFromOffset;
				End += TweenTransitionOptions.TranslationToOffset;
			}

			StartOpacity = TweenTransitionOptions.FadeFrom;
			EndOpacity = TweenTransitionOptions.FadeTo;
			Duration = TweenTransitionOptions.TransitionTime;
			EasingType = TweenTransitionOptions.EasingType;
			break;
	}

	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	UBUITween::Create(this, Duration)
		.FromTranslation(Start)
		.ToTranslation(End)
		.FromOpacity(StartOpacity)
		.ToOpacity(EndOpacity)
		.Easing(EasingType)
		.OnComplete(FBUITweenSignature::CreateLambda(
			[WidgetTransitionMode, WeakThis](UWidget* Owner)
			{
				if (UCoreWidget* Widget = WeakThis.Get())
				{
					Widget->HandleOnWidgetAnimationCompleted(WidgetTransitionMode);
				}
			}
		))
		.Begin();
}

void UCoreWidget::Fade(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	float Start = 0;
	float End = 0;
	float Duration = 0;
	EBUIEasingType EasingType = EBUIEasingType::Linear;

	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			Start = TweenTransitionOptions.FadeFrom;
			End = TweenTransitionOptions.FadeTo;
			Duration = TweenTransitionOptions.TransitionTime;
			EasingType = TweenTransitionOptions.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			Start = TweenTransitionOptions.FadeFrom;
			End = TweenTransitionOptions.FadeTo;
			Duration = TweenTransitionOptions.TransitionTime;
			EasingType = TweenTransitionOptions.EasingType;
			break;
	}

	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	UBUITween::Create(this, Duration)
		.FromOpacity(Start)
		.ToOpacity(End)
		.Easing(EasingType)
		.OnComplete(FBUITweenSignature::CreateLambda(
			[WidgetTransitionMode, WeakThis](UWidget* Owner)
			{
				if (UCoreWidget* Widget = WeakThis.Get())
				{
					Widget->HandleOnWidgetAnimationCompleted(WidgetTransitionMode);
				}
			}
		))
		.Begin();
}
