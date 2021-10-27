// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_FindRandomSpotFood.h"

#include "AI/AIEnemyController.h"
#include "AI/AIEnemyManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_FindRandomSpotFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		TArray<ASpotFood*> ListSpotFoodToIgnore = AIController->GetListAlreadyCheckedSpotFood();
		ListSpotFoodToIgnore.Add(AIController->GetCurrentSpotFoodTarget());
		ASpotFood * NextSpotFood = dynamic_cast<ASpotFood*>(AIController->GetAIEnemyManager()->GetFoodManager()->GetRandomSpotFood(ListSpotFoodToIgnore));

		if(NextSpotFood == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		AIController->SetNextTargetSpotFood(NextSpotFood);
		AIController->GetBlackboardComponent()->SetValueAsBool("NeedNewSpot", false);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AIController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;

}

