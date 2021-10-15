// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameInterface.h"

#include "MainGameMode.h"

AInGameInterface::AInGameInterface()
{
	
}

void AInGameInterface::BeginPlay()
{
	Super::BeginPlay();
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

void AInGameInterface::Pause()
{
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			// Mise en pause du jeu
			UGameplayStatics::SetGamePaused(GetWorld(),true);
			// Activation de la souris
			APlayerController* Player = GetWorld()->GetFirstPlayerController();
			if (Player)
			{
				Player->bShowMouseCursor = true; 
				Player->bEnableClickEvents = true; 
				Player->bEnableMouseOverEvents = true;
			}
			MenuWidget->AddToViewport();
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