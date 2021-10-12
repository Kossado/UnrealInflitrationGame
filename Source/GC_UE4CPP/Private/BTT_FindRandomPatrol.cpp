// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomPatrol.h"

#include "IAEnnemyCharacterController.h"
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
		
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "Next position " + NextAIPatrolPoint->GetName());

		IAController->SetNextTargetAIPatrolPoint(NextAIPatrolPoint);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
	}
	
	return EBTNodeResult::Succeeded;

}

