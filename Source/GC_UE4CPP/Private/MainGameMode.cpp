// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "Hero.h"
#include "PlayerControllerTeam.h"
#include "Kismet/GameplayStatics.h"

AMainGameMode::AMainGameMode()
{
	// Define default classes
	GameStateClass = AMainGameState::StaticClass();
	PlayerControllerClass = APlayerControllerTeam::StaticClass();
}

void AMainGameMode::InitGameState()
{
	Super::InitGameState();
	if(GetGameState<AMainGameState>())
	{
		GetGameState<AMainGameState>()->StoredFood = 0;
		GetGameState<AMainGameState>()->PickableFood = 0;
		GetGameState<AMainGameState>()->StoredFoodToWin = 5;
	}
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"InitGameState");
}

void AMainGameMode::StartPlay()
{
	GetGameState<AMainGameState>()->CurrentGameState = EGS_PLAYING;
	Super::StartPlay();
	InGameInterface = Cast<AGC_InGameInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
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
	if(InGameInterface)
		InGameInterface->UpdateCurrentFood(GetStoredFood());
	CheckGameConditions();
}

void AMainGameMode::LaunchMenuPause()
{
	if(InGameInterface)
		InGameInterface->Pause();
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
		DisableCharacterInput();
	}
	/*if(CharacterHitByAI)
	{
		SetCurrentGameState(EGS_DEFEAT);
		DisableCharacterInput();
	}*/
}

void AMainGameMode::DisableCharacterInput()
{
	// Disable input
	UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));

	// method to pause the game -> Will be useful for the menu, TO DELETE HERE
	//UGameplayStatics::SetGamePaused(GetWorld(),true);
	
	// Method to restart the game Useful later // TO DELETE
	//RestartGame();
}

bool AMainGameMode::GetLaunchGame()
{
	return GetGameState<AMainGameState>()->LaunchGame;
}

void AMainGameMode::SetLaunchGame()
{
	UE_LOG(LogTemp, Warning, TEXT("bbbbbbbbbbbbbbbbbbbb") );
	GetGameState<AMainGameState>()->LaunchGame = false;
}