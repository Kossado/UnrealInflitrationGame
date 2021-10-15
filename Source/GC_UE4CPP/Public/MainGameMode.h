// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameState.h"
#include "GameFramework/GameMode.h"
#include "GC_UE4CPP/HUD/InGameInterface.h"
#include "MainGameMode.generated.h"

/**
 * 
 */

UCLASS()
class GC_UE4CPP_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMainGameMode();
	
	virtual void InitGameState() override;
	virtual void StartPlay() override;

	// Getters
	EGameState GetCurrentGameState() const;
	int GetStoredFood() const;
	int GetPickableFood() const;
	int GetStoredFoodToWin() const;
	// Setters
	void SetCurrentGameState(EGameState CurrentGameState) const;
	void IncrementStoredFood();
	void IncrementPickableFood();
	// Checks
	void CheckGameConditions();
	void DisableCharacterInput();
	// Pause
	void LaunchMenuPause();
	// UI
	AInGameInterface* InGameInterface;
	
};
// if NourritureDansCachette >= QtéDef : GameState = VICTORY
// if Hit by IA : GameState = DEFEAT
// if Menu Open : GameState = PAUSE
// DEFAULT : GameState = PLAYING 