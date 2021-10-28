#include "HUD/ChooseHeroMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UChooseHeroMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIBack)
	{
		UIBack->OnClicked.AddDynamic(this,&UChooseHeroMenuWidget::Back);
	}
	if(UIConfirm)
	{
		UIConfirm->OnClicked.AddDynamic(this,&UChooseHeroMenuWidget::Confirm);
	}
}

// Acquisition principal menu widget
void UChooseHeroMenuWidget::InitializePrincipalMenuWidget(UWidget* principalMenuWidget)
{
	PrincipalMenuWidget = principalMenuWidget;
}

// Event OnCliked in UIBack
void UChooseHeroMenuWidget::Back()
{
	// Update widget visibility 
	this->SetVisibility(ESlateVisibility::Hidden);
	PrincipalMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

// Event OnCliked in UIConfirm
void UChooseHeroMenuWidget::Confirm()
{
	// Update widget visibility 
	this->SetVisibility(ESlateVisibility::Hidden);
	PrincipalMenuWidget->SetVisibility(ESlateVisibility::Visible);

	// Change input mode to game only
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		
	// Disable mouse
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

	// Open level map
	UGameplayStatics::OpenLevel(this, FName(FString("Level1Map")), false);
}

