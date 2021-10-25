#include "GC_InGameInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGC_InGameInterface::AGC_InGameInterface()
{
	
}

void AGC_InGameInterface::BeginPlay()
{
	Super::BeginPlay();
	// Score Menu
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UGC_ScoreMenuWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
	// Pause Menu
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UGC_PauseMenuWidget>(GetWorld(), PauseWidgetClass);
		if (PauseWidget)
		{
			PauseWidget->AddToViewport();
			PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Options Menu
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UGC_OptionsMenuWidget>(GetWorld(), OptionsWidgetClass);
		if (OptionsWidget)
		{
			OptionsWidget->AddToViewport();
			OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// Initialize pour Options Menu et Pause Menu
	if (OptionsWidget && OptionsWidget)
	{
		PauseWidget->InitializeOptionsWidget(OptionsWidget);
		OptionsWidget->InitializePauseWidget(PauseWidget);
	}
}

void AGC_InGameInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGC_InGameInterface::DrawHUD()
{
	Super::DrawHUD();
}

void AGC_InGameInterface::Pause()
{
	if (PauseWidgetClass)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(GetWorld(),true);
		
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeUIOnly InputMode;
		Player->SetInputMode(InputMode);
		Player->bShowMouseCursor = true;
	}
}

void AGC_InGameInterface::UpdateCurrentFood(int32 value)
{
	if(ScoreWidget)
	{
		ScoreWidget->UpdateCurrentFood(value);
	}
}
