// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_LookForActor.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UBTT_LookForActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;

	public:
	UBTT_LookForActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
