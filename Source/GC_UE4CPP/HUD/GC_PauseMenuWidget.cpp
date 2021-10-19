// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_PauseMenuWidget.h"

#include "MainGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UGC_PauseMenuWidget::UGC_PauseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGC_PauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(UIResume)
	{
		UIResume->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Resume);
	}
	if(UIRestart)
	{
		UIRestart->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Restart);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Quit);
	}
}

void UGC_PauseMenuWidget::Resume()
{
	if(UIResume)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::SetGamePaused(GetWorld(),false);
		
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		Player->bShowMouseCursor = false;
	}
}

void UGC_PauseMenuWidget::Restart()
{
	if(UIRestart)
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		
		AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	}
}

void UGC_PauseMenuWidget::Quit()
{
	if(UIQuit)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}