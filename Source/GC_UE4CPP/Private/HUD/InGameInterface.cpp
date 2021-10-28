// Import intern class
#include "HUD/InGameInterface.h"

// Import extern class
#include "Kismet/GameplayStatics.h" //For UGameplayStatics
#include "Components/TextBlock.h"
//#include "Runtime/UMG/Public/UMG.h" //For UTextBlock

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
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - ScoreWidget null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - ScoreWidgetClass null"));
	}
	
	// Create pause menu widget 
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseWidgetClass);
		if (PauseWidget)
		{
			PauseWidget->AddToViewport();
			// Not visible by default
			PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - PauseWidget null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - PauseWidgetClass null"));
	}
	
	// Create options menu widget 
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UOptionsMenuWidget>(GetWorld(), OptionsWidgetClass);
		if (OptionsWidget)
		{
			OptionsWidget->AddToViewport();
			// Not visible by default
			OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - OptionsWidget null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - OptionsWidgetClass null"));
	}
	
	// Initialize to options menu and pause menu
	if (PauseWidget && OptionsWidget)
	{
		PauseWidget->InitializeOptionsWidget(OptionsWidget);
		OptionsWidget->InitializePauseWidget(PauseWidget);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - PauseWidget or/and OptionsWidget null"));
	}
	
	// Create game status menu widget 
	if (GameStatusWidgetClass)
	{
		GameStatusWidget = CreateWidget<UGameStatusWidget>(GetWorld(), GameStatusWidgetClass);
		if (GameStatusWidget)
		{
			GameStatusWidget->AddToViewport();
			// Not visible by default
			GameStatusWidget->SetVisibility(ESlateVisibility::Hidden);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - GameStatusWidget null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::BeginPlay - GameStatusWidgetClass null"));
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

		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		if (Player)
		{
			// Change input mode to UI only
			Player->SetInputMode(FInputModeUIOnly());

			// Activate mouse
			Player->bShowMouseCursor = true;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::Pause - Player null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::Pause - PauseWidgetClass null"));
	}
}

// Function to launch game status menu
void AInGameInterface::EndGame(bool GameStatus)
{
	if (GameStatusWidgetClass)
	{
		if (ScoreWidget && GameStatusWidget)
		{
			// Update widget visibility
			ScoreWidget->SetVisibility(ESlateVisibility::Hidden);
			GameStatusWidget->SetVisibility(ESlateVisibility::Visible);

			// Update editable text in depends on the value provided as parameter of this function
			if (GameStatusWidget->UITitreVictory && GameStatusWidget->UITitreDefeat)
			{
				if (GameStatus)
				{
					GameStatusWidget->UITitreVictory->SetVisibility(ESlateVisibility::Visible);
				} else {
					GameStatusWidget->UITitreDefeat->SetVisibility(ESlateVisibility::Visible);
				}
			} else {
				UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::EndGame - UITitreVictory or/and UITitreDefeat null"));
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::EndGame - ScoreWidget or/and GameStatusWidget null"));
		}

		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		if (Player)
		{
			// Change input mode to UI only
			Player->SetInputMode(FInputModeUIOnly());

			// Activate mouse
			Player->bShowMouseCursor = true;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::EndGame - Player null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::EndGame - GameStatusWidgetClass null"));
	}
}

// Function to update current food
void AInGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AInGameInterface::UpdateCurrentFood - ScoreWidget null"));
	}
}
