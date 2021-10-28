// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCGameState.h"
#include "Characters/LinkSkeletalMeshAnimation.h"
#include "AI/AIEnemyManager.h"
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

	FORCEINLINE bool IsRunning() const { return GetCurrentGameState() == EGS_PLAYING; }
	
	// Getters
	EGameState GetCurrentGameState() const;
	int GetStoredFood() const;
	int GetPickableFood() const;
	int GetStoredFoodToWin() const;
	// Setters
	void SetCurrentGameState(EGameState CurrentGameState) const;
	ESkinPlayer GetSkinPlayer() const;
	USkeletalMesh* GetSkeletalMeshChoosenByPlayer() const;
	TSubclassOf<UAnimInstance> GetAnimationChoosenByPlayer() const;

	void SetSkinPlayer(ESkinPlayer SkinPlayer) const;
	void IncrementStoredFood();
	void IncrementPickableFood();
	// Checks
	void CheckGameConditions();

	void Defeat();
	void DisableCharacterInput();
	// Pause
	void LaunchMenuPause();
	
	int GetPlayerTeamId() const { return PlayerTeamId;}
	
	TArray<LinkSkeletalMeshAnimation> GetTeamSkeletalMeshes(int TeamId) const;
	

private:
	// UI
	AInGameInterface* InGameInterface = nullptr;

	TArray<LinkSkeletalMeshAnimation> ListSkeletalMeshWithAnimations;
	
	int PlayerTeamId;
	TArray<TArray<LinkSkeletalMeshAnimation>> TeamSkeletalMeshes;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMeshKnight;
	
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UAnimInstance> AnimClassKnight;
	
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMeshMaleGoblin;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<UAnimInstance> AnimClassMaleGoblin;
	
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMeshFemaleGoblin;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<UAnimInstance> AnimClassFemaleGoblin;
	
	UPROPERTY(EditAnywhere)
	TArray<int> Team1IdCharacter;

	UPROPERTY(EditAnywhere)
	TArray<int> Team2IdCharacter;

	AFoodManager * FoodManager = nullptr;;
	AAIEnemyManager * EnemyManager = nullptr;;

};