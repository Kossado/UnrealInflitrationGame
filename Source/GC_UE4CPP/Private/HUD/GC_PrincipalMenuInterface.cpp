// Import intern class
#include "HUD/GC_PrincipalMenuInterface.h"

// Event begin play
void AGC_PrincipalMenuInterface::BeginPlay()
{
	Super::BeginPlay();
	// Create principal menu widget 
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UGC_MainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();

			// Change input mode to UI only
			APlayerController* Player = GetWorld()->GetFirstPlayerController();
			FInputModeUIOnly InputMode;
			Player->SetInputMode(InputMode);

			// Activate mouse
			Player->bShowMouseCursor = true;
		}
	}
}

void AGC_PrincipalMenuInterface::DrawHUD()
{
	Super::DrawHUD();
}