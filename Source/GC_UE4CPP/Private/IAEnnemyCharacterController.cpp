// Fill out your copyright notice in the Description page of Project Settings.


#include "IAEnnemyCharacterController.h"
#include "IAEnnemyManager.h"

bool AIAEnnemyCharacterController::Initialize(AIAEnnemyManager* IAEnnemyManagerSpawner, AIACharacter* CharacterToControl, TArray<AIASpotFoodPoint *> ListSpotFoodsPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint)
{
	return Super::Initialize(IAEnnemyManagerSpawner, CharacterToControl, TArray<AIAPatrolPoint*>(ListSpotFoodsPoints), SetUnSpawnPatrolPoint);
}