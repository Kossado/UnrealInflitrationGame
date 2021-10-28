// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_FollowDirectionTarget.h"

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
		
		static const FName NAME_LookNextPositionLine = FName(TEXT("LookNextPosition"));
	
		FHitResult HitResult;

		FVector LocationLostTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector("LastLocationSawPlayer");
		FVector DirectionTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector("DirectionTakenByTarget");
		
		bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, LocationLostTarget, LocationLostTarget+DirectionTarget*5000
		, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
		, FCollisionQueryParams(NAME_LookNextPositionLine, true, OwnerComp.GetOwner()));
		
		if (bHitSocket == true) {
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("LocationSearchPlayer", HitResult.Location-DirectionTarget*50);	
		}
	}
	
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AIController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;

}
