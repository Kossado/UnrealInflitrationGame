// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_DropFood.h"

#include "AI/AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_DropFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		AIController->DropFood();
	}

	return EBTNodeResult::Succeeded;
}
