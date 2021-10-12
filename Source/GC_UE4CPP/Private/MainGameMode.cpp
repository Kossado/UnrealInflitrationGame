// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "Hero.h"

AMainGameMode::AMainGameMode()
{
	// Define default classes
	GameStateClass = AMainGameState::StaticClass();
}

void AMainGameMode::InitGameState()
{
	Super::InitGameState();
	GetGameState<AMainGameState>()->StoredFood = 0;
	GetGameState<AMainGameState>()->PickableFood = 0;
	GetGameState<AMainGameState>()->StoredFoodToWin = 5;
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"InitGameState");
}

void AMainGameMode::StartPlay()
{
	GetGameState<AMainGameState>()->CurrentGameState = EGS_PLAYING;
	Super::StartPlay();
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"StartPlay");
}

EGameState AMainGameMode::GetCurrentGameState() const
{
	return GetGameState<AMainGameState>()->CurrentGameState;
}

int AMainGameMode::GetStoredFood() const
{
	return GetGameState<AMainGameState>()->StoredFood;
}

int AMainGameMode::GetPickableFood() const
{
	return GetGameState<AMainGameState>()->PickableFood;
}

int AMainGameMode::GetStoredFoodToWin() const
{
	return GetGameState<AMainGameState>()->StoredFoodToWin;
}

void AMainGameMode::SetCurrentGameState(EGameState CurrentGameState) const
{
	GetGameState<AMainGameState>()->CurrentGameState = CurrentGameState;
}

void AMainGameMode::IncrementStoredFood()
{
	GetGameState<AMainGameState>()->StoredFood++;
	CheckGameConditions();
}

void AMainGameMode::IncrementPickableFood()
{
	GetGameState<AMainGameState>()->PickableFood++;
}

void AMainGameMode::CheckGameConditions()
{
	if(GetStoredFood() >= GetStoredFoodToWin())
	{
		SetCurrentGameState(EGS_VICTORY);
	}
}