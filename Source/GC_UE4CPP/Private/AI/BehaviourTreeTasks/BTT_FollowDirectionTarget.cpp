// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_FollowDirectionTarget.h"

#include "DrawDebugHelpers.h"
#include "AI/AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_FollowDirectionTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		if(OwnerComp.GetBlackboardComponent() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get Blackboard from BehaviorTree"));
			return EBTNodeResult::Failed;
		}
		
		static const FName NAME_AILineOfSight = FName(TEXT("LookNextPosition"));
	
		FHitResult HitResult;

		FVector LocationLostTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector("LastLocationSawPlayer");
		FVector EndDirectionTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector("DirectionTakenByTarget");

		DrawDebugLine(GetWorld(), LocationLostTarget, EndDirectionTarget, FColor::Blue, false, 5);
		
		bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, LocationLostTarget, EndDirectionTarget
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
			, FCollisionQueryParams(NAME_AILineOfSight, true, OwnerComp.GetOwner()));
		
		if (bHitSocket == true) {
			bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, HitResult.Location, HitResult.Location-FVector::UpVector*500
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
			, FCollisionQueryParams(NAME_AILineOfSight, true, HitResult.GetActor()));

			if(bHitSocket == true)
			{
				DrawDebugLine(GetWorld(), LocationLostTarget, HitResult.Location + (LocationLostTarget - HitResult.Location).GetSafeNormal() * 100, FColor::Red, false, 5);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("LocationSearchPlayer", HitResult.Location + (LocationLostTarget - HitResult.Location).GetSafeNormal() * 100);	
			}
		}
	}
	
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AIController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;

}
