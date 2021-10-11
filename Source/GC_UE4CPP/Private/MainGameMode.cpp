// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

AMainGameMode::AMainGameMode()
{
	GameStateClass = AMainGameState::StaticClass();
}

void AMainGameMode::StartPlay()
{
	GetWorld()->GetAuthGameMode()->GetGameState<AMainGameState>()->CurrentGameState = EGS_PLAYING;
	GetWorld()->GetAuthGameMode()->GetGameState<AMainGameState>()->StoredFood = 0;
	GetWorld()->GetAuthGameMode()->GetGameState<AMainGameState>()->PickableFood = 0;
	GetWorld()->GetAuthGameMode()->GetGameState<AMainGameState>()->StoredFoodToWin = 5;
	
	Super::StartPlay();
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

void AMainGameMode::SetCurrentGameState(EGameState CurrentGameState)
{
	GetGameState<AMainGameState>()->CurrentGameState = CurrentGameState;
}

void AMainGameMode::IncrementStoredFood()
{
	GetGameState<AMainGameState>()->StoredFood++;
	CheckGameState();
}

void AMainGameMode::IncrementPickableFood()
{
	GetGameState<AMainGameState>()->PickableFood++;
}

void AMainGameMode::CheckGameState()
{
	if(GetStoredFood() >= GetStoredFoodToWin())
	{
		SetCurrentGameState(EGS_VICTORY);
	}
}
