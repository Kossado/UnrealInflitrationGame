#include "MenuPrincipalGameMode.h"

AMenuPrincipalGameMode::AMenuPrincipalGameMode() : Super()
{
	
}

void AMenuPrincipalGameMode::StartPlay()
{
	Super::StartPlay();
	MenuPrincipalInterface = Cast<APrincipalMenuInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

