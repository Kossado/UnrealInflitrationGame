// Import intern class
#include "HUD/PauseMenuWidget.h"
#include "Managers/GCGameMode.h"

// Import extern class
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Constructor
void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIResume)
	{
		UIResume->OnClicked.AddDynamic(this,&UPauseMenuWidget::Resume);
	}
	if(UIRestart)
	{
		UIRestart->OnClicked.AddDynamic(this,&UPauseMenuWidget::Restart);
	}
	if(UIOptions)
	{
		UIOptions->OnClicked.AddDynamic(this,&UPauseMenuWidget::Options);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UPauseMenuWidget::Quit);
	}
	if(UIQuitDesktop)
	{
		UIQuitDesktop->OnClicked.AddDynamic(this,&UPauseMenuWidget::QuitDesktop);
	}
	if(UIQuitMainMenu)
	{
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UPauseMenuWidget::QuitMainMenu);
	}
}

// Acquisition options widget
void UPauseMenuWidget::InitializeOptionsWidget(UWidget* optionsWidget)
{
	OptionsWidget = optionsWidget;
}

// Event OnCliked in UIResume
void UPauseMenuWidget::Resume()
{
	if(UIResume)
	{
		// Update widget visibility 
		this->SetVisibility(ESlateVisibility::Hidden);

		// Resume play
		UGameplayStatics::SetGamePaused(GetWorld(),false);

		// Change input mode to game only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);

		// Disable mouse
		Player->bShowMouseCursor = false;

		// Update button visibility
		if (this->UIQuitDesktop->IsVisible())
		{
			this->UIQuitDesktop->SetVisibility(ESlateVisibility::Hidden);
			this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

// Event OnCliked in UIRestart
void UPauseMenuWidget::Restart()
{
	if(UIRestart)
	{
		// Change input mode to game only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);

		// Restart game
		AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	}
}

// Event OnCliked in UIOptions
void UPauseMenuWidget::Options()
{
	if(UIOptions)
	{
		// Update widget visibility 
		this->SetVisibility(ESlateVisibility::Hidden);
		OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

// Event OnCliked in UIQuit
void UPauseMenuWidget::Quit()
{
	if(UIQuit && UIQuitDesktop && UIQuitMainMenu)
	{
		// Activation or desactivation visibilty for UIQuitDesktop and UIQuitMainMenu button
		if (this->UIQuitDesktop->IsVisible())
		{
			this->UIQuitDesktop->SetVisibility(ESlateVisibility::Hidden);
			this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Hidden);
		} else {
			this->UIQuitDesktop->SetVisibility(ESlateVisibility::Visible);
			this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

// Event OnCliked in UIQuitDesktop
void UPauseMenuWidget::QuitDesktop()
{
	if(UIQuitDesktop)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}

// Event OnCliked in UIQuitMainMenu
void UPauseMenuWidget::QuitMainMenu()
{
	if(UIQuitMainMenu)
	{
		// Update game state 
		AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->SetCurrentGameState(EGS_PLAYING);

		// Open level principal menu
		UGameplayStatics::OpenLevel(this, FName(FString("MenuPrincipal")), false);
	}
}