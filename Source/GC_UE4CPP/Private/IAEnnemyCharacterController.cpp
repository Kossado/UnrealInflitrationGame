// Fill out your copyright notice in the Description page of Project Settings.


#include "IAEnnemyCharacterController.h"
#include "IAEnnemyManager.h"
#include "IASpotFoodPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

bool AIAEnnemyCharacterController::Initialize(AIAEnnemyManager* IAEnnemyManagerSpawner, TArray<AIASpotFoodPoint *> ListSpotFoodsPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint, unsigned int NbRetriesBeforeBackUnSpawn)
{
	if(!Super::Initialize(IAEnnemyManagerSpawner, TArray<AIAPatrolPoint*>(ListSpotFoodsPoints), SetUnSpawnPatrolPoint))
	{
		return false;
	}

	IAEnnemyManager = IAEnnemyManagerSpawner;
	this->NbRetriesBeforeBack = NbRetriesBeforeBackUnSpawn; 

	return true;
}

bool AIAEnnemyCharacterController::IsSpotHasFood(AIASpotFoodPoint * SpotFood)
{
	if(SpotFood == nullptr)
	{
		return false;
	}
	
	if(SpotFood->GetFoodState())
	{
		return true;
	}

	else
	{
		return false;
	}
}

AIAEnnemyManager* AIAEnnemyCharacterController::GetIAEnnemyManager() const
{
	return IAEnnemyManager;
}

void AIAEnnemyCharacterController::SetNextTargetAIPatrolPoint(AIASpotFoodPoint * NextTargetAIPatrolPoint)
{
	Super::SetNextTargetAIPatrolPoint(NextTargetAIPatrolPoint);
	Blackboard->SetValueAsObject("SpotFood", NextTargetAIPatrolPoint);

	NbRetriesBeforeBack--;

	if(NbRetriesBeforeBack <= 0)
	{
		Blackboard->SetValueAsBool("GoUnSpawn", true);
	}
}
