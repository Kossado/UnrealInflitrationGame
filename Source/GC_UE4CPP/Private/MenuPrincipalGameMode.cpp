#include "MenuPrincipalGameMode.h"

AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	
}

void AMenuPrincipalGameMode::StartPlay()
{
	Super::StartPlay();
	MenuPrincipalInterface = Cast<APrincipalMenuInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

