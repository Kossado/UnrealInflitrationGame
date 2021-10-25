// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_PutFoodAtStand.h"

#include "AI/AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_PutFoodAtStand::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		ASpotFood * CurrentSpotFood = dynamic_cast<ASpotFood*>(AIController->GetCurrentSpotFoodTarget());

		if(CurrentSpotFood == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		///If there is food, we need a new spot		
		if(CurrentSpotFood->HasFood())
		{
			AIController->WillNeedNewDestination();			
			AIController->GetBlackboardComponent()->SetValueAsBool("NeedNewSpot", true);
			return EBTNodeResult::Failed;
		}

		else
		{
			AIController->PutFoodAtStand();
			AIController->GetBlackboardComponent()->SetValueAsBool("NeedNewSpot", false);
			AIController->GetBlackboardComponent()->SetValueAsBool("GoUnSpawn", true);

			return EBTNodeResult::Succeeded;
		}

	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AIController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	

}
