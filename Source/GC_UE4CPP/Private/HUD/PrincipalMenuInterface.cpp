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
	if (ChooseHeroMenuWidgetClass)
	{
		ChooseHeroMenuWidget = CreateWidget<UChooseHeroMenuWidget>(GetWorld(), ChooseHeroMenuWidgetClass);
		if (ChooseHeroMenuWidget)
		{
			ChooseHeroMenuWidget->AddToViewport();
			ChooseHeroMenuWidget->SetVisibility(ESlateVisibility::Hidden);

			ChooseHeroMenuWidget->InitializePrincipalMenuWidget(MainMenuWidget);
		}
	}
	// Initialize to choose hero menu and principal menu
	if (ChooseHeroMenuWidget && MainMenuWidget)
	{
		ChooseHeroMenuWidget->InitializePrincipalMenuWidget(MainMenuWidget);
		MainMenuWidget->InitializeChooseHeroMenuWidget(ChooseHeroMenuWidget);
	}
}

void APrincipalMenuInterface::DrawHUD()
{
	Super::DrawHUD();
}