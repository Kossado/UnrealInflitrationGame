// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckSpawnFood.h"
#include "IAEnnemyCharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_CheckSpawnFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAEnnemyCharacterController * IAController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner()))
	{
		AIASpotFoodPoint * CurrentAIPatrolPoint = dynamic_cast<AIASpotFoodPoint*>(IAController->GetCurrentAIPatrolPoint());

		if(CurrentAIPatrolPoint == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		IAController->GetBlackboardComponent()->SetValueAsBool("NeedNewSpot", !IAController->IsSpotHasFood(CurrentAIPatrolPoint));
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
	}
	
	return EBTNodeResult::Succeeded;

}