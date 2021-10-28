// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCGameState.h"
#include "GameFramework/GameMode.h"
#include "HUD/InGameInterface.h"
#include "GCGameMode.generated.h"

/**
 * 
 */

class AFoodManager;
class AAIEnemyManager;

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
	void Defeat();
	void DisableCharacterInput();
	// Pause
	void LaunchMenuPause();

	FORCEINLINE int GetSelectedMeshForPlayer() const { return GameState->PlayerMeshId;}
	FORCEINLINE int GetPlayerTeamId() const { return GameState->PlayerTeamId;}
	
	TArray<USkeletalMesh*> GetTeamSkeletalMeshes(int TeamId) const;
	

private:
	// UI
	AInGameInterface* InGameInterface;

	TArray<TArray<USkeletalMesh*>> TeamSkeletalMeshes;
	
	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> Team1SkeletalMeshes;

	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> Team2SkeletalMeshes;

	AFoodManager * FoodManager;
	AAIEnemyManager * EnemyManager;
	
};
// if NourritureDansCachette >= QtéDef : GameState = VICTORY
// if Hit by AI : GameState = DEFEAT
// if Menu Open : GameState = PAUSE
// DEFAULT : GameState = PLAYING 