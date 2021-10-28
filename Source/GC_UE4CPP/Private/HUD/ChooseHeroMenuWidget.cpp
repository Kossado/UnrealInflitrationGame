#include "HUD/ChooseHeroMenuWidget.h"

#include "GCGameMode.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
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
	if(UIPersonnageHero)
	{
		UIPersonnageHero->OnCheckStateChanged.AddDynamic(this,&UChooseHeroMenuWidget::CheckHero);
	}
	if(UIPersonnageGobelinMale)
	{
		UIPersonnageGobelinMale->OnCheckStateChanged.AddDynamic(this,&UChooseHeroMenuWidget::CheckGobelinMale);
	}
	if(UIPersonnageGobelinFemale)
	{
		UIPersonnageGobelinFemale->OnCheckStateChanged.AddDynamic(this,&UChooseHeroMenuWidget::CheckGobelinFemale);
	}
}

// Acquisition principal menu widget
void UChooseHeroMenuWidget::InitializePrincipalMenuWidget(UWidget* principalMenuWidget)
{
	PrincipalMenuWidget = principalMenuWidget;
}

// Event OnCheckStateChanged in UIPersonnageHero
void UChooseHeroMenuWidget::CheckHero(bool IsCheck)
{
	if (IsCheck)
	{
		UIPersonnageGobelinMale->SetCheckedState(ECheckBoxState::Unchecked);
		UIPersonnageGobelinFemale->SetCheckedState(ECheckBoxState::Unchecked);
		CurrentSkinPlayer = EGS_KNIGHT;
	}
}

// Event OnCheckStateChanged in UIPersonnageGobelinMale
void UChooseHeroMenuWidget::CheckGobelinMale(bool IsCheck)
{
	if (IsCheck)
	{
		UIPersonnageHero->SetCheckedState(ECheckBoxState::Unchecked);
		UIPersonnageGobelinFemale->SetCheckedState(ECheckBoxState::Unchecked);
		CurrentSkinPlayer = EGS_GOBELIN_MALE;
	}
}

// Event OnCheckStateChanged in UIPersonnageGobelinFemale
void UChooseHeroMenuWidget::CheckGobelinFemale(bool IsCheck)
{
	if (IsCheck)
	{
		UIPersonnageHero->SetCheckedState(ECheckBoxState::Unchecked);
		UIPersonnageGobelinMale->SetCheckedState(ECheckBoxState::Unchecked);
		CurrentSkinPlayer = EGS_GOBELIN_FEMALE;
	}
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
	// Save choose of player : update game state
	AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CurrentSkinPlayer)
	{
		GameMode->SetSkinPlayer(CurrentSkinPlayer);
	} else {
		return; // Error of player : No item selected
	}
	
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

