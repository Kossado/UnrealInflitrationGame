// Import intern class
#include "HUD/ChooseHeroMenuWidget.h"
#include "Managers/GCGameMode.h"
#include "Managers/GCGameInstance.h"

// Import extern class
#include "Components/Button.h" // For UButton
#include "Components/CheckBox.h" // For UCheckBox
#include "Kismet/GameplayStatics.h" // For UGameplayStatics

// Constructor
void UChooseHeroMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIBack && UIConfirm && UIPersonnageHero && UIPersonnageGobelinMale && UIPersonnageGobelinFemale)
	{
		UIBack->OnClicked.AddDynamic(this,&UChooseHeroMenuWidget::Back);
		UIConfirm->OnClicked.AddDynamic(this,&UChooseHeroMenuWidget::Confirm);
		UIPersonnageHero->OnCheckStateChanged.AddDynamic(this,&UChooseHeroMenuWidget::CheckHero);
		UIPersonnageGobelinMale->OnCheckStateChanged.AddDynamic(this,&UChooseHeroMenuWidget::CheckGobelinMale);
		UIPersonnageGobelinFemale->OnCheckStateChanged.AddDynamic(this,&UChooseHeroMenuWidget::CheckGobelinFemale);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::NativeConstruct - One or more UButton is/are null"));
	}
}

// Acquisition principal menu widget
void UChooseHeroMenuWidget::InitializePrincipalMenuWidget(UWidget* principalMenuWidget)
{
	if (principalMenuWidget)
	{
		PrincipalMenuWidget = principalMenuWidget;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::InitializePrincipalMenuWidget - principalMenuWidget null"));
	}
}

// Event OnCheckStateChanged in UIPersonnageHero
void UChooseHeroMenuWidget::CheckHero(bool IsCheck)
{
	if (IsCheck)
	{
		if (UIPersonnageGobelinMale && UIPersonnageGobelinFemale)
		{
			UIPersonnageGobelinMale->SetCheckedState(ECheckBoxState::Unchecked);
			UIPersonnageGobelinFemale->SetCheckedState(ECheckBoxState::Unchecked);
			CurrentSkinPlayer = EGS_KNIGHT;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::CheckHero - UIPersonnageGobelinMale or/and UIPersonnageGobelinFemale null"));
		}
	}
}

// Event OnCheckStateChanged in UIPersonnageGobelinMale
void UChooseHeroMenuWidget::CheckGobelinMale(bool IsCheck)
{
	if (IsCheck)
	{
		if (UIPersonnageHero && UIPersonnageGobelinFemale)
		{
			UIPersonnageHero->SetCheckedState(ECheckBoxState::Unchecked);
			UIPersonnageGobelinFemale->SetCheckedState(ECheckBoxState::Unchecked);
			CurrentSkinPlayer = EGS_GOBELIN_MALE;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::CheckGobelinMale - UIPersonnageHero or/and UIPersonnageGobelinFemale null"));
		}
	}
}

// Event OnCheckStateChanged in UIPersonnageGobelinFemale
void UChooseHeroMenuWidget::CheckGobelinFemale(bool IsCheck)
{
	if (IsCheck)
	{
		if (UIPersonnageHero && UIPersonnageGobelinMale)
		{
			UIPersonnageHero->SetCheckedState(ECheckBoxState::Unchecked);
			UIPersonnageGobelinMale->SetCheckedState(ECheckBoxState::Unchecked);
			CurrentSkinPlayer = EGS_GOBELIN_FEMALE;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::CheckGobelinFemale - UIPersonnageHero or/and UIPersonnageGobelinMale null"));
		}
	}
}

// Event OnCliked in UIBack
void UChooseHeroMenuWidget::Back()
{
	// Update game instance (to use the choose of player in other level)
	UGCGameInstance* GameInstance = Cast<UGCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance && UIPersonnageHero && UIPersonnageGobelinMale && UIPersonnageGobelinFemale)
	{
		CurrentSkinPlayer = EGS_NO_SKIN;
		UIPersonnageHero->SetCheckedState(ECheckBoxState::Unchecked);
		UIPersonnageGobelinMale->SetCheckedState(ECheckBoxState::Unchecked);
		UIPersonnageGobelinFemale->SetCheckedState(ECheckBoxState::Unchecked);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::Back - A object is null"));
	}
	
	// Update widget visibility 
	this->SetVisibility(ESlateVisibility::Hidden);
	if (PrincipalMenuWidget)
	{
		PrincipalMenuWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::Back - PrincipalMenuWidget null"));
	}
}

// Event OnCliked in UIConfirm
void UChooseHeroMenuWidget::Confirm()
{
	// Update game instance (to use the choose of player in other level)
	UGCGameInstance* GameInstance = Cast<UGCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		if (CurrentSkinPlayer != EGS_NO_SKIN)
		{
			GameInstance->SetSkinPlayer(CurrentSkinPlayer);

			// Update widget visibility 
			this->SetVisibility(ESlateVisibility::Hidden);
			if (PrincipalMenuWidget)
			{
				PrincipalMenuWidget->SetVisibility(ESlateVisibility::Visible);
			} else {
				UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::Confirm - PrincipalMenuWidget null"));
			}

			APlayerController* Player = GetWorld()->GetFirstPlayerController();
			if (Player)
			{
				// Change input mode to game only
				Player->SetInputMode(FInputModeGameOnly());
		
				// Disable mouse
				Player->bShowMouseCursor = false;
			} else {
				UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::Confirm - Player null"));
			}

			// Open level map
			UGameplayStatics::OpenLevel(this, FName(FString("Level1Map")), false);
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UChooseHeroMenuWidget::Confirm - GameInstance null"));
	}
}

