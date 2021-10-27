// Import intern class
#include "HUD/PrincipalMenuWidget.h"

// Import extern class
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/UMG/Public/UMG.h"

// Constructor
void UPrincipalMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIPlay)
	{
		UIPlay->OnClicked.AddDynamic(this,&UPrincipalMenuWidget::Play);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UPrincipalMenuWidget::Quit);
	}
}

// Event OnCliked in UIPlay
void UPrincipalMenuWidget::Play()
{
	if(UIPlay)
	{
		// Change input mode to game only
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		
		// Disable mouse
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

		// Open level map
		UGameplayStatics::OpenLevel(this, FName(FString("Level1Map")), false);
	}
}

// Event OnCliked in UIQuit
void UPrincipalMenuWidget::Quit()
{
	if(UIQuit)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}