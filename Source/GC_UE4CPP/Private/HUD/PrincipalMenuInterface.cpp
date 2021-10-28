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

			APlayerController* Player = GetWorld()->GetFirstPlayerController();
			if (Player)
			{
				// Change input mode to UI only
				Player->SetInputMode(FInputModeUIOnly());

				// Activate mouse
				Player->bShowMouseCursor = true;
			} else {
				UE_LOG(LogTemp, Warning, TEXT("APrincipalMenuInterface::BeginPlay - Player null"));
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("APrincipalMenuInterface::BeginPlay - MainMenuWidget null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("APrincipalMenuInterface::BeginPlay - MainMenuWidgetClass null"));
	}
	
	// Create choose hero menu widget (hidden by default)
	if (ChooseHeroMenuWidgetClass)
	{
		ChooseHeroMenuWidget = CreateWidget<UChooseHeroMenuWidget>(GetWorld(), ChooseHeroMenuWidgetClass);
		if (ChooseHeroMenuWidget)
		{
			ChooseHeroMenuWidget->AddToViewport();
			ChooseHeroMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("APrincipalMenuInterface::BeginPlay - ChooseHeroMenuWidget null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("APrincipalMenuInterface::BeginPlay - ChooseHeroMenuWidgetClass null"));
	}
	
	// Initialize to choose hero menu and principal menu
	if (ChooseHeroMenuWidget && MainMenuWidget)
	{
		ChooseHeroMenuWidget->InitializePrincipalMenuWidget(MainMenuWidget);
		MainMenuWidget->InitializeChooseHeroMenuWidget(ChooseHeroMenuWidget);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("APrincipalMenuInterface::BeginPlay - ChooseHeroMenuWidget or/and MainMenuWidget null"));
	}
}

void APrincipalMenuInterface::DrawHUD()
{
	Super::DrawHUD();
}