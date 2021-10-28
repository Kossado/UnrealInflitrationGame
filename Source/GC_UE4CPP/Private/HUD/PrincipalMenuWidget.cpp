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

// Acquisition choose hero menu widget
void UPrincipalMenuWidget::InitializeChooseHeroMenuWidget(UWidget* chooseHeroMenuWidget)
{
	ChooseHeroMenuWidget = chooseHeroMenuWidget;
}

// Event OnCliked in UIPlay
void UPrincipalMenuWidget::Play()
{
	if(UIPlay)
	{
		// Update widget visibility 
		this->SetVisibility(ESlateVisibility::Hidden);
		ChooseHeroMenuWidget->SetVisibility(ESlateVisibility::Visible);
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