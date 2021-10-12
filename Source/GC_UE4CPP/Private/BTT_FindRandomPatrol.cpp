// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomPatrol.h"

#include "AIController.h"
#include "IAPatrolPoint.h"
#include "IAPawnController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/UnrealMathUtility.h"

#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAPawnController * IAController = Cast<AIAPawnController>(OwnerComp.GetAIOwner()))
	{
		AIAPatrolPoint * NextAIPatrolPoint = IAController->GetRandomAIPatrolPoint(true);

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

