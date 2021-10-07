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
	VICTORY,
	DEFEAT,
	PAUSE,
	PLAYING
};

UCLASS()
class GC_UE4CPP_API AMainGameState : public AGameState
{
	GENERATED_BODY()

private:
	bool bVictory;

public:
	EGameState GameState;
	// if NourritureDansCachette >= QtéDef : GameState = VICTORY
	// if Hit by IA : GameState = DEFEAT
	// if Menu Open : GameState = PAUSE
	// DEFAULT : GameState = PLAYING 
	
};
