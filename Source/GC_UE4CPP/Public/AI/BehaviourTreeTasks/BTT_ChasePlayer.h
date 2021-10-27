// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"


#include "BTT_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UBTT_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere)
		ACharacter * Player;
	
	EBTNodeResult::Type virtual ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
