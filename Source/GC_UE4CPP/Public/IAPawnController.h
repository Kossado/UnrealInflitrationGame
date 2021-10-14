// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IAPatrolPoint.h"
#include "IACharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "IAPawnController.generated.h"

/**
 * 
 */

class AIAPawnManager;

UCLASS()
class GC_UE4CPP_API AIAPawnController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AIACharacter * CharacterControlled;

	UPROPERTY(EditAnywhere)
	UBehaviorTreeComponent * BehaviorComponent;

	// UPROPERTY(EditAnywhere)
	// UBlackboardComponent * BlackboardComponent;


	// Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGoKey; // Location/point for the AI to go to

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey; // reference to the players location

	public:
	AIAPawnController (const FObjectInitializer & ObjectInitializer);

	// FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	FORCEINLINE TArray<AIAPatrolPoint*> GetPatrolPoints() const { return PatrolPoints; }

	
	AIAPatrolPoint * GetCurrentAIPatrolPoint();
	AIAPatrolPoint * GetNextAIPatrolPoint();
	AIAPatrolPoint * GetRandomAIPatrolPoint(bool ExcludeCurrentPosition);
	AIAPatrolPoint * GetUnSpawnPatrolPoint() const;

	AIAPawnManager * GetIAPawnManager() const;

protected:
	bool Initialize(AIAPawnManager* IAPawnManagerSpawner, const TArray<AIAPatrolPoint *> ListPatrolPoints, AIAPatrolPoint * UnSpawnPatrolPoint);
	void SetNextTargetAIPatrolPoint(AIAPatrolPoint * NextTargetAIPatrolPoint);

	virtual void OnUnPossess() override;

private:
	TArray<AIAPatrolPoint*> PatrolPoints;
	AIAPatrolPoint* UnSpawnPatrolPoint;
	
	int CurrentTargetPatrolPoints=-1;
	AIAPawnManager * IAPawnerManager;
};