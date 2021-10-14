// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_CheckSpawnFood.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UBTT_CheckSpawnFood : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;
};
