// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPrincipalGameMode.h"

AMenuPrincipalGameMode::AMenuPrincipalGameMode() : Super()
{
	
}

void AMenuPrincipalGameMode::StartPlay()
{
	Super::StartPlay();
	MenuPrincipalInterface = Cast<AGC_MenuPrincipalInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

