#include "GC_MenuPrincipalInterface.h"

AGC_MenuPrincipalInterface::AGC_MenuPrincipalInterface()
{
	
}

void AGC_MenuPrincipalInterface::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UGC_MainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		
			APlayerController* Player = GetWorld()->GetFirstPlayerController();
			FInputModeUIOnly InputMode;
			Player->SetInputMode(InputMode);
			Player->bShowMouseCursor = true;
		}
	}
}

void AGC_MenuPrincipalInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGC_MenuPrincipalInterface::DrawHUD()
{
	Super::DrawHUD();
}