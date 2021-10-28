// Import intern class
#include "HUD/PauseMenuWidget.h"
#include "Managers/GCGameMode.h"

// Import extern class
#include "Components/Button.h" // For UButton
#include "Kismet/GameplayStatics.h" // For UGameplayStatics and UKismetSystemLibrary

// Constructor
void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIResume && UIRestart && UIOptions && UIQuit && UIQuitDesktop && UIQuitMainMenu)
	{
		UIResume->OnClicked.AddDynamic(this,&UPauseMenuWidget::Resume);
		UIRestart->OnClicked.AddDynamic(this,&UPauseMenuWidget::Restart);
		UIOptions->OnClicked.AddDynamic(this,&UPauseMenuWidget::Options);
		UIQuit->OnClicked.AddDynamic(this,&UPauseMenuWidget::Quit);
		UIQuitDesktop->OnClicked.AddDynamic(this,&UPauseMenuWidget::QuitDesktop);
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UPauseMenuWidget::QuitMainMenu);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::NativeConstruct - One or more UButton is/are null"));
	}
}

// Acquisition options widget
void UPauseMenuWidget::InitializeOptionsWidget(UWidget* optionsWidget)
{
	if (optionsWidget)
	{
		OptionsWidget = optionsWidget;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::InitializeOptionsWidget - optionsWidget null"));
	}
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

		
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		if (Player)
		{
			// Change input mode to game only
			Player->SetInputMode(FInputModeGameOnly());

			// Disable mouse
			Player->bShowMouseCursor = false;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Resume - Player null"));
		}
		

		// Update button visibility
		if (UIQuitDesktop && UIQuitMainMenu)
		{
			if (this->UIQuitDesktop->IsVisible())
			{
				this->UIQuitDesktop->SetVisibility(ESlateVisibility::Hidden);
				this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Hidden);
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Resume - UIQuitDesktop or/and UIQuitMainMenu null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Resume - UIResume null"));
	}
}

// Event OnCliked in UIRestart
void UPauseMenuWidget::Restart()
{
	if(UIRestart)
	{
		// Change input mode to game only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		if (Player)
		{
			Player->SetInputMode(FInputModeGameOnly());
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Restart - Player null"));
		}

		// Restart game
		AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Restart - UIRestart null"));
	}
}

// Event OnCliked in UIOptions
void UPauseMenuWidget::Options()
{
	if(UIOptions && OptionsWidget)
	{
		// Update widget visibility 
		this->SetVisibility(ESlateVisibility::Hidden);
		OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Options - UIOptions or/and OptionsWidget null"));
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
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::Quit - UIQuit or/and UIQuitDesktop or/and UIQuitMainMenu null"));
	}
}

// Event OnCliked in UIQuitDesktop
void UPauseMenuWidget::QuitDesktop()
{
	// Quit game
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
}

// Event OnCliked in UIQuitMainMenu
void UPauseMenuWidget::QuitMainMenu()
{
	// Update game state 
	AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->SetCurrentGameState(EGS_PLAYING);

		// Open level principal menu
		UGameplayStatics::OpenLevel(this, FName(FString("MenuPrincipal")), false);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPauseMenuWidget::QuitMainMenu - GameMode null"));
	}
}