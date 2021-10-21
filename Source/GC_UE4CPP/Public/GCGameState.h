// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GCGameState.generated.h"

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
class GC_UE4CPP_API AGCGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGCGameState();
	// Current state of the game
	EGameState CurrentGameState;
	// Quantity of food stored in the hideout
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GameData)
	int StoredFood;
	// Quantity of food in the map, excluding those in the hideout
	UPROPERTY(VisibleAnywhere, Category=GameData)
	int PickableFood;
	// Quantity of food needed to win the game
	UPROPERTY(VisibleAnywhere, Category=GameData)
	int StoredFoodToWin;
};
