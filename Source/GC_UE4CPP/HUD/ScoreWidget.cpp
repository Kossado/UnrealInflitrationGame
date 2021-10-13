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
		//TXTCombo->SetText(FText::FromString(FString::FromInt(value) + "x Combo"));
		UIProgression->SetPercent(value * 0.20f);
	}

	/*if(TXTCombo)
	{
		TXTCombo->SetText(FText::FromString(FString::FromInt(value) + "x Combo"));
	}*/
}