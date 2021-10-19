// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GCBTT_LookAround.generated.h"


struct FBTLookAroundTaskMemory
{
	/** Move request ID */
	FAIRequestID RotateRequestID;

	FDelegateHandle BBObserverDelegateHandle;
	FVector PreviousRotateGoalLocation;

	uint8 bWaitingForPath : 1;
	uint8 bObserverCanFinishTask : 1;
};

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGCBTT_LookAround : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;

};
