// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_UnSpawn.h"
#include "AI/AIEnemyController.h"
#include "AI/AIEnemyManager.h"
#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_UnSpawn::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		AAIEnemyManager * EnemyManager =AIController->GetAIEnemyManager();

		if(EnemyManager == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		EnemyManager->UnSpawnAIAndPrepareRespawn(AIController);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AIController from BehaviorTree"));
	}
	
	return EBTNodeResult::Succeeded;

}