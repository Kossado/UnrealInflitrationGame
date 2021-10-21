// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCGameState.h"
#include "GameFramework/GameMode.h"
#include "GC_UE4CPP/HUD/GC_InGameInterface.h"
#include "GCGameMode.generated.h"

/**
 * 
 */

UCLASS()
class GC_UE4CPP_API AGCGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGCGameMode();
	
	virtual void InitGameState() override;
	virtual void StartPlay() override;
	virtual void RestartGame() override;

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
	AGC_InGameInterface* InGameInterface;
	
};
// if NourritureDansCachette >= QtéDef : GameState = VICTORY
// if Hit by IA : GameState = DEFEAT
// if Menu Open : GameState = PAUSE
// DEFAULT : GameState = PLAYING 