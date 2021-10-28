// Import intern class
#include "HUD/PrincipalMenuWidget.h"

// Import extern class
#include "Components/Button.h" // For UButton
#include "Kismet/KismetSystemLibrary.h" // For UKismetSystemLibrary

// Constructor
void UPrincipalMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIPlay && UIQuit)
	{
		UIPlay->OnClicked.AddDynamic(this,&UPrincipalMenuWidget::Play);
		UIQuit->OnClicked.AddDynamic(this,&UPrincipalMenuWidget::Quit);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPrincipalMenuWidget::NativeConstruct - UIPlay ou/et UIQuit null"));
	}
}

// Acquisition choose hero menu widget
void UPrincipalMenuWidget::InitializeChooseHeroMenuWidget(UWidget* chooseHeroMenuWidget)
{
	if (chooseHeroMenuWidget)
	{
		ChooseHeroMenuWidget = chooseHeroMenuWidget;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPrincipalMenuWidget::InitializeChooseHeroMenuWidget - chooseHeroMenuWidget null"));
	}
}

// Event OnCliked in UIPlay
void UPrincipalMenuWidget::Play()
{
	if(UIPlay && ChooseHeroMenuWidget)
	{
		// Update widget visibility 
		this->SetVisibility(ESlateVisibility::Hidden);
		ChooseHeroMenuWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPrincipalMenuWidget::Play - UIPlay or/and ChooseHeroMenuWidget null"));
	}
}

// Event OnCliked in UIQuit
void UPrincipalMenuWidget::Quit()
{
	if(UIQuit)
	{
		// Quit game
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UPrincipalMenuWidget::Quit - UIQuit null"));
	}
}