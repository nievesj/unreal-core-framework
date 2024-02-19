// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UI/CoreWidget.h"

#include "Animation/UMGSequencePlayer.h"
#include "BUITween.h"
#include "Components/CanvasPanel.h"

void UCoreWidget::Show()
{
	switch (WidgetAnimationType)
	{
		case EWidgetAnimationType::WidgetTween:
			if (CanvasPanel)
			{
				PlayTweenTransition(WidgetTweenTransitionOptionsIntro, EWidgetTransitionMode::Intro);
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
				PlayTweenTransition(WidgetTweenTransitionOptionsOuttro, EWidgetTransitionMode::Outtro);
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
			OnShown();
			break;
		case EWidgetTransitionMode::Outtro:
			OnHidden();
			break;
	}
}

void UCoreWidget::PlayTweenTransition(const FWidgetTweenTransitionOptions& TweenTransitionOptions, const EWidgetTransitionMode WidgetTransitionMode)
{
	FWidgetTransform WidgetTransform = CanvasPanel->GetRenderTransform();
	//const FGeometry& Geometry = GetCachedGeometry();
	FVector2D Size = GetDesiredSize();
	switch (TweenTransitionOptions.TransitionType)
	{
		case EWidgetTransitionType::NotUsed:
			break;
		case EWidgetTransitionType::Scale:
			Scale(TweenTransitionOptions, WidgetTransitionMode);
			break;
		case EWidgetTransitionType::Left:
			break;
		case EWidgetTransitionType::Right:
			break;
		case EWidgetTransitionType::Top:
			break;
		case EWidgetTransitionType::Bottom:
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
			Duration = WidgetTweenTransitionOptionsIntro.TransitionTime;
			EasingType = WidgetTweenTransitionOptionsIntro.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			Start = TweenTransitionOptions.MaxScale;
			End = TweenTransitionOptions.MinScale;
			Duration = WidgetTweenTransitionOptionsOuttro.TransitionTime;
			EasingType = WidgetTweenTransitionOptionsOuttro.EasingType;
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

void UCoreWidget::Move(FVector2D Start, FVector2D End, const EWidgetTransitionMode WidgetTransitionMode)
{
	TWeakObjectPtr<UCoreWidget> WeakThis = this;
	UBUITween::Create(this, 0.5f)
		.FromTranslation(Start)
		.ToTranslation(End)
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
			Start = TweenTransitionOptions.FadeMinVisibility;
			End = TweenTransitionOptions.FadeMaxVisibility;
			Duration = WidgetTweenTransitionOptionsIntro.TransitionTime;
			EasingType = WidgetTweenTransitionOptionsIntro.EasingType;
			break;
		case EWidgetTransitionMode::Outtro:
			Start = TweenTransitionOptions.FadeMaxVisibility;
			End = TweenTransitionOptions.FadeMinVisibility;
			Duration = WidgetTweenTransitionOptionsOuttro.TransitionTime;
			EasingType = WidgetTweenTransitionOptionsOuttro.EasingType;
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
