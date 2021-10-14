// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

UScoreWidget::UScoreWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScoreWidget::UpdateCurrentFood(int32 value)
{
	if(UIProgression)
	{
		UIProgression->SetPercent(value * 0.20f);
	}
}