// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTT_MoveToFood.generated.h"

/**
 * 
 */


UCLASS()
class GC_UE4CPP_API UBTT_MoveToFood : public UBTTask_MoveTo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxAcceptableRadius;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
public:
	UBTT_MoveToFood(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
