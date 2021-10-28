// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_MoveToFood.h"

#include "DrawDebugHelpers.h"
#include "Food/Food.h"
#include "Food/SpotFood.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTT_MoveToFood::UBTT_MoveToFood(const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
	NodeName = "Move To Food";

	bReachTestIncludesAgentRadius = false;
	bReachTestIncludesGoalRadius = false;
}

EBTNodeResult::Type UBTT_MoveToFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{		
		UObject* KeyValue = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	
		AFood* TargetFood = Cast<AFood>(KeyValue);
		if (TargetFood /*&& !TargetFood->IsOnGround()*/)
		{
			FVector Origin;
			FVector Extents;

			if(TargetFood->GetBoundsSupportFood(Origin, Extents))
			{
				float SmallerSide = FMath::Min<float>(Extents.X, Extents.Y);

				if(SmallerSide <= MaxAcceptableRadius)
				{
					AcceptableRadius = SmallerSide*1.5f;
				}
			}
		}

		else
		{
			ASpotFood * TargetFoodSpot = Cast<ASpotFood>(KeyValue);

			if (TargetFoodSpot /*&& !TargetFoodSpot->IsOnGround()*/)
			{
				FVector Origin;
				FVector Extents;

				if(TargetFoodSpot->GetBoundsSupportFood(Origin, Extents))
				{
					float SmallerSide = FMath::Min<float>(Extents.X, Extents.Y);

					if(SmallerSide <= MaxAcceptableRadius)
					{
						AcceptableRadius = SmallerSide*1.5f;
					}
				}
			}

			else
			{
				UE_LOG(LogTemp, Error, TEXT("Unknown type"));
			}
		}
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
