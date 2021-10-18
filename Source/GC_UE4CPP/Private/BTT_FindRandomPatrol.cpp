// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomPatrol.h"

#include "IAEnnemyCharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAEnnemyCharacterController * IAController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner()))
	{
		AIASpotFoodPoint * NextAIPatrolPoint = dynamic_cast<AIASpotFoodPoint*>(IAController->GetRandomAIPatrolPoint(true));

		if(NextAIPatrolPoint == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		IAController->SetNextTargetAIPatrolPoint(NextAIPatrolPoint);
		IAController->GetBlackboardComponent()->SetValueAsBool("NeedNewSpot", false);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;

}

