// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomPatrol.h"

#include "AIController.h"
#include "AIPatrolPoint.h"
#include "MyIAController.h"
#include "PatrolPoints.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/UnrealMathUtility.h"

#include "BehaviorTree/BlackboardData.h"

EBTNodeResult::Type UBTT_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AMyIAController * IAController = Cast<AMyIAController>(OwnerComp.GetAIOwner()))
	{
		AActor * NextAIPatrolPoint = IAController->GetRandomAIPatrolPoint(true);
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "Next position " + NextAIPatrolPoint->GetName());

		IAController->SetNextTargetAIPatrolPoint(NextAIPatrolPoint);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
	}
	
	return EBTNodeResult::Succeeded;

}

