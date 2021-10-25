#include "GC_PrincipalMenuInterface.h"

AGC_PrincipalMenuInterface::AGC_PrincipalMenuInterface()
{
	
}

void AGC_PrincipalMenuInterface::BeginPlay()
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
	if (GameStatusWidgetClass)
	{
		GameStatusWidget = CreateWidget<UGameStatusWidget>(GetWorld(), GameStatusWidgetClass);
		if (GameStatusWidget)
		{
			GameStatusWidget->AddToViewport();
			GameStatusWidget->SetVisibility(ESlateVisibility::Hidden);

			APlayerController* Player = GetWorld()->GetFirstPlayerController();
			FInputModeUIOnly InputMode;
			Player->SetInputMode(InputMode);
			Player->bShowMouseCursor = true;
		}
	}
}

void AGC_PrincipalMenuInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGC_PrincipalMenuInterface::DrawHUD()
{
	Super::DrawHUD();
}