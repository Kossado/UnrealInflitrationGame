// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameInterface.h"

AInGameInterface::AInGameInterface()
{
	
}

void AInGameInterface::BeginPlay()
{
	Super::BeginPlay();
	if (ComboWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ComboWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

void AInGameInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInGameInterface::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	}
}