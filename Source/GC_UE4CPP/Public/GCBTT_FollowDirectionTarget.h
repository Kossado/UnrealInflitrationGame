// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GCBTT_FollowDirectionTarget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGCBTT_FollowDirectionTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;

	
};
