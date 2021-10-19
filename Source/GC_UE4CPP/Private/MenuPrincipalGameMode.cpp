// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPrincipalGameMode.h"

AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	
}

void AMenuPrincipalGameMode::StartPlay()
{
	Super::StartPlay();
	MenuPrincipalInterface = Cast<AGC_MenuPrincipalInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

