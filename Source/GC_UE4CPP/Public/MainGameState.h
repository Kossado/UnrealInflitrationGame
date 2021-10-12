// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UENUM()
enum EGameState
{
	EGS_VICTORY,
	EGS_DEFEAT,
	EGS_PAUSE,
	EGS_PLAYING
};

UCLASS()
class GC_UE4CPP_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	bool bVictory;

public:
	// Current state of the game
	EGameState CurrentGameState;
	// Quantity of food stored in the hideout
	UPROPERTY(VisibleAnywhere)
	int StoredFood;
	// Quantity of food in the map, excluding those in the hideout
	UPROPERTY(VisibleAnywhere)
	int PickableFood;
	// Quantity of food needed to win the game
	UPROPERTY(VisibleAnywhere)
	int StoredFoodToWin;	
};
