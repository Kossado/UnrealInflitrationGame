// Import intern class
#include "HUD/GameStatusWidget.h"
#include "Managers/GCGameMode.h"

// Import extern class
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

// Constructor
void UGameStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIPlayAgain)
	{
		UIPlayAgain->OnClicked.AddDynamic(this,&UGameStatusWidget::PlayAgain);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGameStatusWidget::Quit);
	}
	if(UIQuitDesktop)
	{
		UIQuitDesktop->OnClicked.AddDynamic(this,&UGameStatusWidget::QuitDesktop);
	}
	if(UIQuitMainMenu)
	{
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UGameStatusWidget::QuitMainMenu);
	}
}

// Event OnCliked in UIPlayAgain
void UGameStatusWidget::PlayAgain()
{
	if(UIPlayAgain)
	{
		// Change input mode to game only
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());

		// Restart game
		AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
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
	}
}

// Event OnCliked in UIQuitDesktop
void UGameStatusWidget::QuitDesktop()
{
	if(UIQuitDesktop)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}

// Event OnCliked in UIQuitMainMenu
void UGameStatusWidget::QuitMainMenu()
{
	if(UIQuitMainMenu)
	{
		// Open level principal menu
		UGameplayStatics::OpenLevel(this, FName(FString("MenuPrincipal")), false);
	}
}