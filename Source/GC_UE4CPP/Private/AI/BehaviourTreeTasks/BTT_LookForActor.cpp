// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTreeTasks/BTT_LookForActor.h"
#include "AI/AIEnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_LookForActor::UBTT_LookForActor(const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
	NodeName = "Look For Actor";
}

EBTNodeResult::Type UBTT_LookForActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AActor * LookingForActor=nullptr; 
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UE_LOG(LogTemp, Warning, TEXT("Key ID is an object %s"), *(GetSelectedBlackboardKey().ToString()));

		UObject* KeyValue = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());

		if(KeyValue)
		{
			UE_LOG(LogTemp, Warning, TEXT("Key ID is an object %s"), *(KeyValue->GetName()));
		}
		
		LookingForActor= Cast<AActor>(KeyValue);
	}

	if(LookingForActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	if(AAIEnemyController * AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner()))
	{
		static const FName NAME_AILineOfSight = FName(TEXT("LookForFood"));

		FHitResult HitResult;
	
		FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_AILineOfSight, true, AIController);

		const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, AIController->GetCharacter()->GetActorLocation(), LookingForActor->GetActorLocation()
				, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
				, CollisionQueryParams);

		if(bHitSocket && !HitResult.GetActor()->IsOwnedBy(LookingForActor))
		{
			return EBTNodeResult::Failed;
		}

		else
		{
			return EBTNodeResult::Succeeded;
		}		
	}

	else
	{
		return EBTNodeResult::Failed;
	}
}
