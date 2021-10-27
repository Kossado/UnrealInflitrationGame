// import class intern
#include "HUD/GC_InGameInterface.h"

// Event begin play
void AGC_InGameInterface::BeginPlay()
{
	Super::BeginPlay();
	// Create score menu widget 
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UGC_ScoreMenuWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
	// Create pause menu widget 
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UGC_PauseMenuWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			// Not visible to default
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Create options menu widget 
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UGC_OptionsMenuWidget>(GetWorld(), OptionsWidgetClass);
		if (OptionsWidget)
		{
			OptionsWidget->AddToViewport();
			// Not visible to default
			OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Initialize to options menu and pause menu
	if (OptionsWidget && OptionsWidget)
	{
		MenuWidget->InitializeOptionsWidget(OptionsWidget);
		OptionsWidget->InitializePauseWidget(MenuWidget);
	}
	// Create game status menu widget 
	if (GameStatusWidgetClass)
	{
		GameStatusWidget = CreateWidget<UGameStatusWidget>(GetWorld(), GameStatusWidgetClass);
		if (GameStatusWidget)
		{
			GameStatusWidget->AddToViewport();
			// Not visible to default
			GameStatusWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AGC_InGameInterface::DrawHUD()
{
	Super::DrawHUD();
}

// Function to launch pause menu
void AGC_InGameInterface::Pause()
{
	if (MenuWidgetClass)
	{
		// Update widget visibility 
		MenuWidget->SetVisibility(ESlateVisibility::Visible);

		// Pause play
		UGameplayStatics::SetGamePaused(GetWorld(),true);

		// Change input mode to UI only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeUIOnly InputMode;
		Player->SetInputMode(InputMode);

		// Activate mouse
		Player->bShowMouseCursor = true;
	}
}

// Function to launch game status menu
void AGC_InGameInterface::EndGame(bool GameStatus)
{
	if (GameStatusWidgetClass)
	{
		// Update widget visibility 
		ScoreWidget->SetVisibility(ESlateVisibility::Hidden);
		GameStatusWidget->SetVisibility(ESlateVisibility::Visible);

		// Update editable text in depends on the value provided as parameter of this function
		if (GameStatus)
		{
			GameStatusWidget->UITitreVictory->SetVisibility(ESlateVisibility::Visible);
		} else {
			GameStatusWidget->UITitreDefeat->SetVisibility(ESlateVisibility::Visible);
		}

		// Change input mode to UI only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeUIOnly InputMode;
		Player->SetInputMode(InputMode);

		// Activate mouse
		Player->bShowMouseCursor = true;
	}
}

// Function to update current food
void AGC_InGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	}
}
