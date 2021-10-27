// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_TakeFood.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UBTT_TakeFood : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;

	public:
	UBTT_TakeFood(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
