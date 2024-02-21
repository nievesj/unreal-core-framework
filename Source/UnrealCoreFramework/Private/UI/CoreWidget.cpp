// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UI/CoreWidget.h"

#include "Animation/UMGSequencePlayer.h"
#include "BUITween.h"
#include "Components/CanvasPanel.h"
#include "Components/Viewport.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

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

void UCoreWidget::Scale(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	FVector2D Start;
	FVector2D End;
	float Duration = 0;
	EBUIEasingType EasingType = EBUIEasingType::Linear;

	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			Start = TweenTransitionOptions.MinScale;
			End = TweenTransitionOptions.MaxScale;
			Duration = TweenEntranceOptions.TransitionTime;
			EasingType = TweenEntranceOptions.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			Start = TweenTransitionOptions.MaxScale;
			End = TweenTransitionOptions.MinScale;
			Duration = TweenExitOptions.TransitionTime;
			EasingType = TweenExitOptions.EasingType;
			break;
	}

	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	UBUITween::Create(this, Duration)
		.FromScale(Start)
		.ToScale(End)
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
	float Duration = 0;
	EBUIEasingType EasingType = EBUIEasingType::Linear;

	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			if (!TweenTransitionOptions.UseViewportAsTranslationOrigin)
			{
				Start = TweenTransitionOptions.StartTranslationVector2D + TweenTransitionOptions.StartTranslationOffset;
				End = TweenTransitionOptions.EndTranslationVector2D + TweenTransitionOptions.EndTranslationOffset;
			}
			else
			{
				GetViewportTranslationVectors(TweenTransitionOptions.WidgetTranslationType, Start, End);
				Start += TweenTransitionOptions.StartTranslationOffset;
				End += TweenTransitionOptions.EndTranslationOffset;
			}
			Duration = TweenEntranceOptions.TransitionTime;
			EasingType = TweenEntranceOptions.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			if (!TweenTransitionOptions.UseViewportAsTranslationOrigin)
			{
				Start = TweenTransitionOptions.StartTranslationVector2D + TweenTransitionOptions.StartTranslationOffset;
				End = TweenTransitionOptions.EndTranslationVector2D + TweenTransitionOptions.EndTranslationOffset;
			}
			else
			{
				GetViewportTranslationVectors(TweenTransitionOptions.WidgetTranslationType, End, Start);
				Start += TweenTransitionOptions.StartTranslationOffset;
				End += TweenTransitionOptions.EndTranslationOffset;
			}
			Duration = TweenExitOptions.TransitionTime;
			EasingType = TweenExitOptions.EasingType;
			break;
	}

	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	UBUITween::Create(this, Duration)
		.FromTranslation(Start)
		.ToTranslation(End)
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

void UCoreWidget::Fade(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	float Start = 0;
	float End = 0;
	float Duration = 0;
	EBUIEasingType EasingType = EBUIEasingType::Linear;

	switch (WidgetTransitionMode)
	{
		case EWidgetTransitionMode::Intro:
			Start = TweenTransitionOptions.FadeMinVisibility;
			End = TweenTransitionOptions.FadeMaxVisibility;
			Duration = TweenEntranceOptions.TransitionTime;
			EasingType = TweenEntranceOptions.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			Start = TweenTransitionOptions.FadeMaxVisibility;
			End = TweenTransitionOptions.FadeMinVisibility;
			Duration = TweenExitOptions.TransitionTime;
			EasingType = TweenExitOptions.EasingType;
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
