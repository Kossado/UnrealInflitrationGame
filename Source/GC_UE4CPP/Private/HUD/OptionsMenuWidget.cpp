// Import intern class
#include "HUD/OptionsMenuWidget.h"

// Import extern class
#include "Components/InputKeySelector.h" // For InputKeySelector
#include "Components/Button.h" // For UButton

// Constructor
void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Initialisation event OnClicked
	if(UIBack && UIConfirm)
	{
		UIBack->OnClicked.AddDynamic(this,&UOptionsMenuWidget::Back);
		UIConfirm->OnClicked.AddDynamic(this,&UOptionsMenuWidget::Confirm);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIBack or/and UIConfirm null"));
	}

	// Acquisition input settings
	InputSettings = UInputSettings::GetInputSettings();

	if (InputSettings)
	{
		// Initialisation several arrays to change input settings
		KeyChange.Init(false,6);
		ActionArrayKeys.Init(FInputActionKeyMapping(),2);
		ActionArrayKeysNext.Init(FInputActionKeyMapping(),2);
		AxisArrayKeys.Init(FInputAxisKeyMapping(),4);
		AxisArrayKeysNext.Init(FInputAxisKeyMapping(),4);

		// Acquisition input key
		TArray <struct FInputActionKeyMapping> OutMappingsInteract;
		InputSettings->GetActionMappingByName("Interact", OutMappingsInteract);
		ActionArrayKeys[0] = OutMappingsInteract[0];
		
		TArray <struct FInputActionKeyMapping> OutMappingsInvokeMenu;
		InputSettings->GetActionMappingByName("InvokeMenu", OutMappingsInvokeMenu);
		ActionArrayKeys[1] = OutMappingsInvokeMenu[0];

		TArray <struct FInputAxisKeyMapping> OutMappingsMoveForward;
		InputSettings->GetAxisMappingByName("MoveForward", OutMappingsMoveForward);
		AxisArrayKeys[1] = OutMappingsMoveForward[0];
		AxisArrayKeys[0] = OutMappingsMoveForward[1];

		TArray <struct FInputAxisKeyMapping> OutMappingsMoveRight;
		InputSettings->GetAxisMappingByName("MoveRight", OutMappingsMoveRight);
		AxisArrayKeys[3] = OutMappingsMoveRight[0];
		AxisArrayKeys[2] = OutMappingsMoveRight[1];

		// Initialisation event OnKeySelected and default value input key
		if(UIActionInteract)
		{
			UIActionInteract->SetSelectedKey(ActionArrayKeys[0].Key);
			UIActionInteract->OnKeySelected.AddDynamic(this, &UOptionsMenuWidget::ChangeKeyInteract);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIActionInteract null"));
		}
		if(UIActionInvokeMenu)
		{
			UIActionInvokeMenu->SetSelectedKey(ActionArrayKeys[1].Key);
			UIActionInvokeMenu->OnKeySelected.AddDynamic(this, &UOptionsMenuWidget::ChangeKeyInvokeMenu);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIActionInvokeMenu null"));
		}
		if(UIAxisMoveForward)
		{
			UIAxisMoveForward->SetSelectedKey(AxisArrayKeys[0].Key);
			UIAxisMoveForward->OnKeySelected.AddDynamic(this, &UOptionsMenuWidget::ChangeKeyMoveForward);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIAxisMoveForward null"));
		}
		if(UIAxisMoveBack)
		{
			UIAxisMoveBack->SetSelectedKey(AxisArrayKeys[1].Key);
			UIAxisMoveBack->OnKeySelected.AddDynamic(this, &UOptionsMenuWidget::ChangeKeyMoveBack);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIAxisMoveBack null"));
		}
		if(UIAxisMoveLeft)
		{
			UIAxisMoveLeft->SetSelectedKey(AxisArrayKeys[2].Key);
			UIAxisMoveLeft->OnKeySelected.AddDynamic(this, &UOptionsMenuWidget::ChangeKeyMoveLeft);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIAxisMoveLeft null"));
		}
		if(UIAxisMoveRight)
		{
			UIAxisMoveRight->SetSelectedKey(AxisArrayKeys[3].Key);
			UIAxisMoveRight->OnKeySelected.AddDynamic(this, &UOptionsMenuWidget::ChangeKeyMoveRight);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - UIAxisMoveRight null"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::NativeConstruct - InputSettings null"));
	}
}

// Event OnKeySelected in UIActionInteract
void UOptionsMenuWidget::ChangeKeyInteract(FInputChord InputChord)
{
	// Save value who is need change, in apporiate array, and declare a changement
	ActionArrayKeysNext[0] = FInputActionKeyMapping("Interact",InputChord.Key);
	KeyChange[0] = true;
}

// Event OnKeySelected in UIActionInvokeMenu
void UOptionsMenuWidget::ChangeKeyInvokeMenu(FInputChord InputChord)
{
	// Save value who is need change, in apporiate array, and declare a changement
	ActionArrayKeysNext[1] = FInputActionKeyMapping("InvokeMenu",InputChord.Key);
	KeyChange[1] = true;
}

// Event OnKeySelected in UIAxisMoveForward
void UOptionsMenuWidget::ChangeKeyMoveForward(FInputChord InputChord)
{
	// Save value who is need change, in apporiate array, and declare a changement
	AxisArrayKeysNext[0] = FInputAxisKeyMapping("MoveForward",InputChord.Key, 1.0f);
	KeyChange[2] = true;
}

// Event OnKeySelected in UIAxisMoveBack
void UOptionsMenuWidget::ChangeKeyMoveBack(FInputChord InputChord)
{
	// Save value who is need change, in apporiate array, and declare a changement
	AxisArrayKeysNext[1] = FInputAxisKeyMapping("MoveForward",InputChord.Key, -1.0f);
	KeyChange[3] = true;
}

// Event OnKeySelected in UIAxisMoveLeft
void UOptionsMenuWidget::ChangeKeyMoveLeft(FInputChord InputChord)
{
	// Save value who is need change, in apporiate array, and declare a changement
	AxisArrayKeysNext[2] = FInputAxisKeyMapping("MoveRight",InputChord.Key, 1.0f);
	KeyChange[4] = true;
}

// Event OnKeySelected in UIAxisMoveRight
void UOptionsMenuWidget::ChangeKeyMoveRight(FInputChord InputChord)
{
	// Save value who is need change, in apporiate array, and declare a changement
	AxisArrayKeysNext[3] = FInputAxisKeyMapping("MoveRight",InputChord.Key, -1.0f);
	KeyChange[5] = true;
}

// Acquisition pause widget
void UOptionsMenuWidget::InitializePauseWidget(UWidget* pauseWidget)
{
	if (pauseWidget)
	{
		PauseWidget = pauseWidget;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::InitializePauseWidget - pauseWidget null"));
	}
}

// Event OnCliked in UIBack
void UOptionsMenuWidget::Back()
{
	// Update widget visibility 
	this->SetVisibility(ESlateVisibility::Hidden);
	if (PauseWidget)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::Back - PauseWidget null"));
	}

	if (UIActionInteract && UIActionInvokeMenu && UIAxisMoveForward && UIAxisMoveBack && UIAxisMoveLeft && UIAxisMoveRight)
	{
		// Reset current input settings to previous input settings
		UIActionInteract->SetSelectedKey(ActionArrayKeys[0].Key);
		UIActionInvokeMenu->SetSelectedKey(ActionArrayKeys[1].Key);
		UIAxisMoveForward->SetSelectedKey(AxisArrayKeys[0].Key);
		UIAxisMoveBack->SetSelectedKey(AxisArrayKeys[1].Key);
		UIAxisMoveLeft->SetSelectedKey(AxisArrayKeys[2].Key);
		UIAxisMoveRight->SetSelectedKey(AxisArrayKeys[3].Key);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::Back - One or more UInputKeySelector is/are null"));
	}
	
	ActionArrayKeysNext.Init(FInputActionKeyMapping(),2);
	AxisArrayKeysNext.Init(FInputAxisKeyMapping(),4);
	KeyChange.Init(false,6);
}

// Event OnCliked in UIConfirm
void UOptionsMenuWidget::Confirm()
{
	// Update widget visibility 
	this->SetVisibility(ESlateVisibility::Hidden);
	if (PauseWidget)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::Confirm - PauseWidget null"));
	}

	if (InputSettings)
	{
		// Update input settings with the new input settings ask by the user
		int y = 0;
		for (int i = 0; i < ActionArrayKeys.Num(); i++)
		{
			if (KeyChange[y])
			{
				InputSettings->RemoveActionMapping(ActionArrayKeys[i]);
				InputSettings->AddActionMapping(ActionArrayKeysNext[i]);
				ActionArrayKeys[i] = ActionArrayKeysNext[i];
				KeyChange[y] = false;
			}
			y++;
		}
		for (int i = 0; i < AxisArrayKeys.Num(); i++)
		{
			if (KeyChange[y])
			{
				InputSettings->RemoveAxisMapping(AxisArrayKeys[i]);
				InputSettings->AddAxisMapping(AxisArrayKeysNext[i]);
				AxisArrayKeys[i] = AxisArrayKeysNext[i];
				KeyChange[y] = false;
			}
			y++;
		}

		// Applies the changes
		InputSettings->ForceRebuildKeymaps();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UOptionsMenuWidget::Confirm - InputSettings null"));
	}
}