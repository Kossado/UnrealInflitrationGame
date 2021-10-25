#include "MenuPrincipalGameMode.h"

AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	
}

void AMenuPrincipalGameMode::StartPlay()
{
	Super::StartPlay();
	PrincipalMenuInterface = Cast<AGC_PrincipalMenuInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

