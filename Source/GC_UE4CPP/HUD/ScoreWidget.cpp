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
	if(TXTCombo)
	{
		TXTCombo->SetText(FText::FromString(FString::FromInt(value) + "x Combo"));
	}
}