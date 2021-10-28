// Import intern class
#include "HUD/GameStatusWidget.h"
#include "Managers/GCGameMode.h"

// Import extern class
#include "Components/Button.h" // For UButton
#include "Kismet/GameplayStatics.h" // For UGameplayStatics and UKismetSystemLibrary

// Constructor
void UGameStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIPlayAgain && UIQuit && UIQuitDesktop && UIQuitMainMenu)
	{
		UIPlayAgain->OnClicked.AddDynamic(this,&UGameStatusWidget::PlayAgain);
		UIQuit->OnClicked.AddDynamic(this,&UGameStatusWidget::Quit);
		UIQuitDesktop->OnClicked.AddDynamic(this,&UGameStatusWidget::QuitDesktop);
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UGameStatusWidget::QuitMainMenu);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::NativeConstruct - One or more UButton is/are null"));
	}
}

// Event OnCliked in UIPlayAgain
void UGameStatusWidget::PlayAgain()
{
	if(UIPlayAgain)
	{
		// Change input mode to game only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		if (Player)
		{
			Player->SetInputMode(FInputModeGameOnly());
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::PlayAgain - Player null"));
		}

		// Restart game
		AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->RestartGame();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::PlayAgain - GameMode null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::PlayAgain - UIPlayAgain null"));
	}
}

// Event OnCliked in UIQuit
void UGameStatusWidget::Quit()
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
		UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::Quit - UIQuit or/and UIQuitDesktop or/and UIQuitMainMenu null"));
	}
}

// Event OnCliked in UIQuitDesktop
void UGameStatusWidget::QuitDesktop()
{
	if(UIQuitDesktop)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::QuitDesktop - UIQuitDesktop null"));
	}
}

// Event OnCliked in UIQuitMainMenu
void UGameStatusWidget::QuitMainMenu()
{
	if(UIQuitMainMenu)
	{
		// Open level principal menu
		UGameplayStatics::OpenLevel(this, FName(FString("MenuPrincipal")), false);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UGameStatusWidget::QuitMainMenu - UIQuitMainMenu null"));
	}
}