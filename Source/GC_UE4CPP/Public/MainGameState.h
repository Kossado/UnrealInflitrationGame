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
	EGameState CurrentGameState;
	UPROPERTY(VisibleAnywhere)
	int StoredFood;
	UPROPERTY(VisibleAnywhere)
	int PickableFood;
	UPROPERTY(VisibleAnywhere)
	int StoredFoodToWin;	
};
