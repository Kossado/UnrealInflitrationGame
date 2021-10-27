#include "HUD/GC_InGameInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGC_InGameInterface::AGC_InGameInterface()
{
	
}

void AGC_InGameInterface::BeginPlay()
{
	Super::BeginPlay();
	// Score Menu
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UGC_ScoreMenuWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
	// Pause Menu
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UGC_PauseMenuWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Options Menu
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UGC_OptionsMenuWidget>(GetWorld(), OptionsWidgetClass);
		if (OptionsWidget)
		{
			OptionsWidget->AddToViewport();
			OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Initialize pour Options Menu et Pause Menu
	if (OptionsWidget && OptionsWidget)
	{
		MenuWidget->InitializeOptionsWidget(OptionsWidget);
		OptionsWidget->InitializePauseWidget(MenuWidget);
	}
	// Game Status Menu
	if (GameStatusWidgetClass)
	{
		GameStatusWidget = CreateWidget<UGameStatusWidget>(GetWorld(), GameStatusWidgetClass);
		if (GameStatusWidget)
		{
			GameStatusWidget->AddToViewport();
			GameStatusWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AGC_InGameInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGC_InGameInterface::DrawHUD()
{
	Super::DrawHUD();
}

void AGC_InGameInterface::Pause()
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
void AGC_InGameInterface::EndGame(bool GameStatus)
{
	if (GameStatusWidgetClass)
	{
		ScoreWidget->SetVisibility(ESlateVisibility::Hidden);
		GameStatusWidget->SetVisibility(ESlateVisibility::Visible);

		if (GameStatus)
		{
			GameStatusWidget->UITitreVictory->SetVisibility(ESlateVisibility::Visible);
		} else {
			GameStatusWidget->UITitreDefeat->SetVisibility(ESlateVisibility::Visible);
		}

		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeUIOnly InputMode;
		Player->SetInputMode(InputMode);
		Player->bShowMouseCursor = true;
	}
}


void AGC_InGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	}
}
