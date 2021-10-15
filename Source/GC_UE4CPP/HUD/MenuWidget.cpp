// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "MainGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(UIResume)
	{
		UIResume->OnClicked.AddDynamic(this,&UMenuWidget::Resume);
	}
	if(UIRestart)
	{
		UIRestart->OnClicked.AddDynamic(this,&UMenuWidget::Restart);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UMenuWidget::Quit);
	}
}

void UMenuWidget::Resume()
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

void UMenuWidget::Restart()
{
	if(UIRestart)
	{
		FInputModeGameOnly InputMode;
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		Player->SetInputMode(InputMode);
		
		AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	}
}

void UMenuWidget::Quit()
{
	if(UIQuit)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}