// Import intern class
#include "HUD/PrincipalMenuInterface.h"

// Event begin play
void APrincipalMenuInterface::BeginPlay()
{
	Super::BeginPlay();
	// Create principal menu widget 
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UPrincipalMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();

			// Change input mode to UI only
			GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

			// Activate mouse
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		}
	}
}

void APrincipalMenuInterface::DrawHUD()
{
	Super::DrawHUD();
}