#include "MenuPrincipalGameMode.h"

AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	
}

void AMenuPrincipalGameMode::StartPlay()
{
	Super::StartPlay();
	MenuPrincipalInterface = Cast<AGC_PrincipalMenuInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

