// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBTT_LookAround.h"

#include "IAEnnemyCharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UGCBTT_LookAround::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAEnnemyCharacterController * IAController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner()))
	{
		GEngine->
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;

}
