// Import intern class
#include "HUD/GC_PauseMenuWidget.h"
#include "GCGameMode.h"

// Import extern class
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

// Constructor
void UGC_PauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIResume)
	{
		UIResume->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Resume);
	}
	if(UIRestart)
	{
		UIRestart->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Restart);
	}
	if(UIOptions)
	{
		UIOptions->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Options);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Quit);
	}
	if(UIQuitDesktop)
	{
		UIQuitDesktop->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::QuitDesktop);
	}
	if(UIQuitMainMenu)
	{
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::QuitMainMenu);
	}
}

// Acquisition options widget
void UGC_PauseMenuWidget::InitializeOptionsWidget(UWidget* optionsWidget)
{
	OptionsWidget = optionsWidget;
}

// Event OnCliked in UIResume
void UGC_PauseMenuWidget::Resume()
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
void UGC_PauseMenuWidget::Restart()
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
void UGC_PauseMenuWidget::Options()
{
	if(UIOptions)
	{
		// Update widget visibility 
		this->SetVisibility(ESlateVisibility::Hidden);
		OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

// Event OnCliked in UIQuit
void UGC_PauseMenuWidget::Quit()
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
void UGC_PauseMenuWidget::QuitDesktop()
{
	if(UIQuitDesktop)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}

// Event OnCliked in UIQuitMainMenu
void UGC_PauseMenuWidget::QuitMainMenu()
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