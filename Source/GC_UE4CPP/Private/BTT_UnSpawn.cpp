// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UnSpawn.h"
#include "IAEnnemyCharacterController.h"
#include "IAEnnemyManager.h"
#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_UnSpawn::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAEnnemyCharacterController * IAController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner()))
	{
		AIAEnnemyManager * EnnemyManager =IAController->GetIAEnnemyManager();

		if(EnnemyManager == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		EnnemyManager->UnSpawnIAAndPrepareRespawn(IAController);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
	}
	
	return EBTNodeResult::Succeeded;

}