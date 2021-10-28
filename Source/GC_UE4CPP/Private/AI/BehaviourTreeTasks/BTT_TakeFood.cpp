// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_TakeFood.h"
#include "AI/AIEnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_TakeFood::UBTT_TakeFood(const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
	NodeName = "Take Food";
}

EBTNodeResult::Type UBTT_TakeFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AFood * FoodToGrab=nullptr; 
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		FoodToGrab= Cast<AFood>(KeyValue);
	}

	if(FoodToGrab == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		if(AIController->IsCarryingFood())
		{
			AIController->DropFood();
		}

		AIController->CarryFood(FoodToGrab);
		return EBTNodeResult::Succeeded;
	}

	else
	{
		return EBTNodeResult::Failed;
	}
}
