// Import intern class
#include "HUD/InGameInterface.h"

// Import extern class
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/UMG.h"

// Event begin play
void AInGameInterface::BeginPlay()
{
	Super::BeginPlay();
	// Create score menu widget 
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreMenuWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
	// Create pause menu widget 
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseWidgetClass);
		if (PauseWidget)
		{
			PauseWidget->AddToViewport();
			// Not visible to default
			PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Create options menu widget 
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UOptionsMenuWidget>(GetWorld(), OptionsWidgetClass);
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
		PauseWidget->InitializeOptionsWidget(OptionsWidget);
		OptionsWidget->InitializePauseWidget(PauseWidget);
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

void AInGameInterface::DrawHUD()
{
	Super::DrawHUD();
}

// Function to launch pause menu
void AInGameInterface::Pause()
{
	if (PauseWidgetClass)
	{
		// Update widget visibility 
		PauseWidget->SetVisibility(ESlateVisibility::Visible);

		// Pause play
		UGameplayStatics::SetGamePaused(GetWorld(),true);

		// Change input mode to UI only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		Player->SetInputMode(FInputModeUIOnly());

		// Activate mouse
		Player->bShowMouseCursor = true;
	}
}

// Function to launch game status menu
void AInGameInterface::EndGame(bool GameStatus)
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
		Player->SetInputMode(FInputModeUIOnly());

		// Activate mouse
		Player->bShowMouseCursor = true;
	}
}

// Function to update current food
void AInGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	}
}
