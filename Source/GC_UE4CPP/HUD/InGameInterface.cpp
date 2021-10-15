// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameInterface.h"

#include "MainGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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
			ScoreWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UGC_MainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
			//UGameplayStatics::SetGamePaused(GetWorld(),true);

			/*APlayerController* Player = GetWorld()->GetFirstPlayerController();
			FInputModeUIOnly InputMode;
			Player->SetInputMode(InputMode);
			Player->bShowMouseCursor = true;*/
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

void AInGameInterface::Pause()
{
	if (MenuWidgetClass)
	{
		MenuWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(GetWorld(),true);
		
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeUIOnly InputMode;
		Player->SetInputMode(InputMode);
		Player->bShowMouseCursor = true;
	}
}

void AInGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	}
}