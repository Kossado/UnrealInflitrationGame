#include "GC_InGameInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGC_InGameInterface::AGC_InGameInterface()
{
	
}

void AGC_InGameInterface::BeginPlay()
{
	Super::BeginPlay();
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UGC_ScoreMenuWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UGC_PauseMenuWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
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
	if (MenuWidgetClass)
	{
		MenuWidget->SetVisibility(ESlateVisibility::Visible);
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