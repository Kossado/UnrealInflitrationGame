// Import intern class
#include "HUD/GC_MainMenuWidget.h"
#include "GCGameMode.h"

// Import extern class
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

// Constructor
void UGC_MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIPlay)
	{
		UIPlay->OnClicked.AddDynamic(this,&UGC_MainMenuWidget::Play);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGC_MainMenuWidget::Quit);
	}
}

// Event OnCliked in UIPlay
void UGC_MainMenuWidget::Play()
{
	if(UIPlay)
	{
		// Change input mode to game only
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		
		// Disable mouse
		Player->bShowMouseCursor = false;

		// Open level map
		UGameplayStatics::OpenLevel(this, FName(FString("Level1Map")), false);
	}
}

// Event OnCliked in UIQuit
void UGC_MainMenuWidget::Quit()
{
	if(UIQuit)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}