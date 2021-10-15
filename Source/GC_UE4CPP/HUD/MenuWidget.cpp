// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "MainGameMode.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMenuWidget::Resume()
{
	if(UIResume)
	{
		UGameplayStatics::SetGamePaused(GetWorld(),false);
		Destruct();
	}
}

void UMenuWidget::Restart()
{
	if(UIRestart)
	{
		AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	}
}

void UMenuWidget::Quit()
{
	if(UIQuit)
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		UKismetSystemLibrary::QuitGame(GetWorld(),Player,EQuitPreference::Quit,true);
	}
}