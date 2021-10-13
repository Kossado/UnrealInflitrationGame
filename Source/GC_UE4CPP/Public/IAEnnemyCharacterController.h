// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAPawnController.h"
#include "IASpotFoodPoint.h"
#include "IAEnnemyCharacterController.generated.h"


class AIAEnnemyManager;

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AIAEnnemyCharacterController : public AIAPawnController
{
	GENERATED_BODY()

public:
	bool Initialize(AIAEnnemyManager* IAEnnemyManagerSpawner, TArray<AIASpotFoodPoint *> ListSpotFoodsPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint, unsigned int NbRetriesBeforeBackUnSpawn);
	void SetNextTargetAIPatrolPoint(AIASpotFoodPoint * NextTargetAIPatrolPoint);
	bool IsSpotHasFood(AIASpotFoodPoint * SpotFood);
	AIAEnnemyManager* GetIAEnnemyManager() const;
private:
	unsigned int NbRetriesBeforeBack;
	AIAEnnemyManager* IAEnnemyManager;
};
