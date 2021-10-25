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
	UE_LOG(LogTemp, Warning, TEXT("Move to food"));

	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Key ID is an object %s"), *(GetSelectedBlackboardKey().ToString()));

		UObject* KeyValue = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());

		if(KeyValue)
		{
			UE_LOG(LogTemp, Warning, TEXT("Key ID is an object %s"), *(KeyValue->GetName()));
		}
		
		AFood* TargetFood = Cast<AFood>(KeyValue);
		if (TargetFood /*&& !TargetFood->IsOnGround()*/)
		{
			UE_LOG(LogTemp, Warning, TEXT("Try move to food"));
			FVector Origin;
			FVector Extents;

			if(TargetFood->GetBoundsSupportFood(Origin, Extents))
			{
				UE_LOG(LogTemp, Warning, TEXT("Center [ %s ] Dimension [ %s ]"), *(Origin.ToString()), *(Extents.ToString()));

				float SmallerSide = FMath::Min<float>(Extents.X, Extents.Y);

				if(SmallerSide <= MaxAcceptableRadius)
				{
					AcceptableRadius = SmallerSide*1.5f;
					UE_LOG(LogTemp, Warning, TEXT("New Acceptable radius %lf"), AcceptableRadius);

				}
			}
		}

		else
		{
			ASpotFood * TargetFoodSpot = Cast<ASpotFood>(KeyValue);

			if (TargetFoodSpot /*&& !TargetFoodSpot->IsOnGround()*/)
			{
				UE_LOG(LogTemp, Warning, TEXT("Try move to food spot"));
				FVector Origin;
				FVector Extents;

				if(TargetFoodSpot->GetBoundsSupportFood(Origin, Extents))
				{
					UE_LOG(LogTemp, Warning, TEXT("Center [ %s ] Dimension [ %s ]"), *(Origin.ToString()), *(Extents.ToString()));

					float SmallerSide = FMath::Min<float>(Extents.X, Extents.Y);

					if(SmallerSide <= MaxAcceptableRadius)
					{
						AcceptableRadius = SmallerSide*1.5f;
						UE_LOG(LogTemp, Warning, TEXT("New Acceptable radius %lf"), AcceptableRadius);
					}
				}
			}

			else
			{
				UE_LOG(LogTemp, Error, TEXT("Unknown type"));
			}
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Acceptable Radius %lf"), AcceptableRadius);

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
