// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameState.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */

UCLASS()
class GC_UE4CPP_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainGameMode();

	virtual void StartPlay() override;

	// Getters
	virtual EGameState GetCurrentGameState() const;
	virtual int GetStoredFood() const;
	virtual int GetPickableFood() const;
	virtual int GetStoredFoodToWin() const;
	// Setters
	virtual void SetCurrentGameState(EGameState CurrentGameState);
	virtual void IncrementStoredFood();
	virtual void IncrementPickableFood();
	// Checks
	virtual void CheckGameState();
	
};
// if NourritureDansCachette >= QtéDef : GameState = VICTORY
// if Hit by IA : GameState = DEFEAT
// if Menu Open : GameState = PAUSE
// DEFAULT : GameState = PLAYING 