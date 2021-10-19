// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_MainMenuWidget.h"

#include "MainGameMode.h"

UGC_MainMenuWidget::UGC_MainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGC_MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(UIPlay)
	{
		UIPlay->OnClicked.AddDynamic(this,&UGC_MainMenuWidget::Play);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGC_MainMenuWidget::Quit);
	}
}

void UGC_MainMenuWidget::Play()
{
	if(UIPlay)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		//FLatentActionInfo LatentInfo;
		//UGameplayStatics::LoadStreamLevel(this, FName(FString("Level1Map")), true, true, LatentInfo);
		UGameplayStatics::SetGamePaused(GetWorld(),false);
		
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		Player->bShowMouseCursor = false;
	}
}

void UGC_MainMenuWidget::Quit()
{
	if(UIQuit)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}