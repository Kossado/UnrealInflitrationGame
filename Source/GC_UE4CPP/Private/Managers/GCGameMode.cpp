// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GCGameMode.h"

#include "KnightPlayerController.h"
#include "Kismet/GameplayStatics.h"

AGCGameMode::AGCGameMode() : Super()
{
	// Define default classes
	GameStateClass = AGCGameState::StaticClass();
	PlayerControllerClass = AKnightPlayerController::StaticClass();
}

void AGCGameMode::InitGameState()
{
	Super::InitGameState();
	if(GetGameState<AGCGameState>())
	{
		GetGameState<AGCGameState>()->StoredFood = 0;
		GetGameState<AGCGameState>()->PickableFood = 0;
		GetGameState<AGCGameState>()->StoredFoodToWin = 5;
	}
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"InitGameState");
}

void AGCGameMode::StartPlay()
{
	GetGameState<AGCGameState>()->CurrentGameState = EGS_PLAYING;
	Super::StartPlay();
	InGameInterface = Cast<AInGameInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AGCGameMode::RestartGame()
{
	Super::RestartGame();
}

EGameState AGCGameMode::GetCurrentGameState() const
{
	return GetGameState<AGCGameState>()->CurrentGameState;
}

int AGCGameMode::GetStoredFood() const
{
	return GetGameState<AGCGameState>()->StoredFood;
}

int AGCGameMode::GetPickableFood() const
{
	return GetGameState<AGCGameState>()->PickableFood;
}

int AGCGameMode::GetStoredFoodToWin() const
{
	return GetGameState<AGCGameState>()->StoredFoodToWin;
}

void AGCGameMode::SetCurrentGameState(EGameState CurrentGameState) const
{
	GetGameState<AGCGameState>()->CurrentGameState = CurrentGameState;
}

void AGCGameMode::SetSkinPlayer(ESkinPlayer SkinPlayer) const
{
	GetGameState<AGCGameState>()->SkinPlayer = SkinPlayer;
}

void AGCGameMode::IncrementStoredFood()
{
	GetGameState<AGCGameState>()->StoredFood++;
	if(InGameInterface)
		InGameInterface->UpdateCurrentFood(GetStoredFood());
	CheckGameConditions();
}

void AGCGameMode::LaunchMenuPause()
{
	if(InGameInterface)
		SetCurrentGameState(EGS_PAUSE);
		InGameInterface->Pause();
}

void AGCGameMode::IncrementPickableFood()
{
	GetGameState<AGCGameState>()->PickableFood++;
}

void AGCGameMode::CheckGameConditions()
{
	if(GetCurrentGameState() == EGS_DEFEAT)
	{
		return;	
	}
	
	if(GetStoredFood() >= GetStoredFoodToWin())
	{
		SetCurrentGameState(EGS_VICTORY);
		DisableCharacterInput();
		if(InGameInterface)
		{
			InGameInterface->EndGame(true);
		}
	}	
}

void AGCGameMode::Defeat()
{
	if(GetCurrentGameState() == EGS_VICTORY)
	{
		return;	
	}
	
	SetCurrentGameState(EGS_DEFEAT);
	DisableCharacterInput();
	if(InGameInterface)
	{
		InGameInterface->EndGame(false);
	}
}

void AGCGameMode::DisableCharacterInput()
{
	// Disable input
	UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
}