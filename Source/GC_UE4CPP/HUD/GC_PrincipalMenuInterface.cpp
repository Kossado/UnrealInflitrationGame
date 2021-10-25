#include "GC_PrincipalMenuInterface.h"

AGC_PrincipalMenuInterface::AGC_PrincipalMenuInterface()
{
	
}

void AGC_PrincipalMenuInterface::BeginPlay()
{
	Super::BeginPlay();
	if (PrincipalMenuWidgetClass)
	{
		PrincipalMenuWidget = CreateWidget<UGC_MainMenuWidget>(GetWorld(), PrincipalMenuWidgetClass);
		if (PrincipalMenuWidget)
		{
			PrincipalMenuWidget->AddToViewport();
		
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