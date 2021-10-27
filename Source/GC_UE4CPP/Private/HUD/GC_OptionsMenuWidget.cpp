#include "HUD/GC_OptionsMenuWidget.h"
#include "GameFramework/InputSettings.h"
#include "Components/InputKeySelector.h"
#include "GameFramework/PlayerInput.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UGC_OptionsMenuWidget::UGC_OptionsMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGC_OptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(UIBack)
	{
		UIBack->OnClicked.AddDynamic(this,&UGC_OptionsMenuWidget::Back);
	}
	if(UIConfirm)
	{
		UIConfirm->OnClicked.AddDynamic(this,&UGC_OptionsMenuWidget::Confirm);
	}

	InputSettings = UInputSettings::GetInputSettings();
	KeyChange.Init(false,6);
	
	ActionArrayKeys.Init(FInputActionKeyMapping(),2);
	ActionArrayKeysNext.Init(FInputActionKeyMapping(),2);

	AxisArrayKeys.Init(FInputAxisKeyMapping(),4);
	AxisArrayKeysNext.Init(FInputAxisKeyMapping(),4);

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
	
	if(UIActionInteract)
	{
		UIActionInteract->SetSelectedKey(ActionArrayKeys[0].Key);
		UIActionInteract->OnKeySelected.AddDynamic(this, &UGC_OptionsMenuWidget::ChangeKeyInteract);
	}
	if(UIActionInvokeMenu)
	{
		UIActionInvokeMenu->SetSelectedKey(ActionArrayKeys[1].Key);
		UIActionInvokeMenu->OnKeySelected.AddDynamic(this, &UGC_OptionsMenuWidget::ChangeKeyInvokeMenu);
	}
	if(UIAxisMoveForward)
	{
		UIAxisMoveForward->SetSelectedKey(AxisArrayKeys[0].Key);
		UIAxisMoveForward->OnKeySelected.AddDynamic(this, &UGC_OptionsMenuWidget::ChangeKeyMoveForward);
	}
	if(UIAxisMoveBack)
	{
		UIAxisMoveBack->SetSelectedKey(AxisArrayKeys[1].Key);
		UIAxisMoveBack->OnKeySelected.AddDynamic(this, &UGC_OptionsMenuWidget::ChangeKeyMoveBack);
	}
	if(UIAxisMoveLeft)
	{
		UIAxisMoveLeft->SetSelectedKey(AxisArrayKeys[2].Key);
		UIAxisMoveLeft->OnKeySelected.AddDynamic(this, &UGC_OptionsMenuWidget::ChangeKeyMoveLeft);
	}
	if(UIAxisMoveRight)
	{
		UIAxisMoveRight->SetSelectedKey(AxisArrayKeys[3].Key);
		UIAxisMoveRight->OnKeySelected.AddDynamic(this, &UGC_OptionsMenuWidget::ChangeKeyMoveRight);
	}
}

void UGC_OptionsMenuWidget::ChangeKeyInteract(FInputChord InputChord)
{
	ActionArrayKeysNext[0] = FInputActionKeyMapping("Interact",InputChord.Key);
	KeyChange[0] = true;
}

void UGC_OptionsMenuWidget::ChangeKeyInvokeMenu(FInputChord InputChord)
{
	ActionArrayKeysNext[1] = FInputActionKeyMapping("InvokeMenu",InputChord.Key);
	KeyChange[1] = true;
}

void UGC_OptionsMenuWidget::ChangeKeyMoveForward(FInputChord InputChord)
{
	AxisArrayKeysNext[0] = FInputAxisKeyMapping("MoveForward",InputChord.Key, 1.0f);
	KeyChange[2] = true;
}

void UGC_OptionsMenuWidget::ChangeKeyMoveBack(FInputChord InputChord)
{
	AxisArrayKeysNext[1] = FInputAxisKeyMapping("MoveForward",InputChord.Key, -1.0f);
	KeyChange[3] = true;
}

void UGC_OptionsMenuWidget::ChangeKeyMoveLeft(FInputChord InputChord)
{
	AxisArrayKeysNext[2] = FInputAxisKeyMapping("MoveRight",InputChord.Key, 1.0f);
	KeyChange[4] = true;
}

void UGC_OptionsMenuWidget::ChangeKeyMoveRight(FInputChord InputChord)
{
	AxisArrayKeysNext[3] = FInputAxisKeyMapping("MoveRight",InputChord.Key, -1.0f);
	KeyChange[5] = true;
}

void UGC_OptionsMenuWidget::InitializePauseWidget(UWidget* pauseWidget)
{
	PauseWidget = pauseWidget;
}

void UGC_OptionsMenuWidget::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);

	UIActionInteract->SetSelectedKey(ActionArrayKeys[0].Key);
	UIActionInvokeMenu->SetSelectedKey(ActionArrayKeys[1].Key);
	UIAxisMoveForward->SetSelectedKey(AxisArrayKeys[0].Key);
	UIAxisMoveBack->SetSelectedKey(AxisArrayKeys[1].Key);
	UIAxisMoveLeft->SetSelectedKey(AxisArrayKeys[2].Key);
	UIAxisMoveRight->SetSelectedKey(AxisArrayKeys[3].Key);
	
	ActionArrayKeysNext.Init(FInputActionKeyMapping(),2);
	AxisArrayKeysNext.Init(FInputAxisKeyMapping(),4);
	KeyChange.Init(false,6);
}

void UGC_OptionsMenuWidget::Confirm()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);

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
	InputSettings->ForceRebuildKeymaps();
}