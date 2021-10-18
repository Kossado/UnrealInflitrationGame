// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBTT_ForgetTarget.h"

#include "IAEnnemyCharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UGCBTT_ForgetTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAEnnemyCharacterController * IAController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner()))
	{
		IAController->ForgetTarget();
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;

}
