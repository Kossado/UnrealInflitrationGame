// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_LookAround.generated.h"


struct GCFBTLookAroundTaskMemory
{
	FRotator InitialRotation;
	float CurrentTimeRotating;
	bool LeftSideAlreadyChecked;
	bool RightSideAlreadyChecked;
};

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UBTT_LookAround : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	virtual uint16 GetInstanceMemorySize() const override;

	public:

	UPROPERTY(EditAnywhere)
	bool LookTwoSidesSeparately;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="LookTwoSidesSeparately", ClampMin = "-180.0", ClampMax = "0.0", UIMin = "-180.0", UIMax = "0.0"))
	float RangeLeft;

	UPROPERTY(EditAnywhere, meta=(EditCondition="LookTwoSidesSeparately", ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))
	float RangeRight;

	UPROPERTY(EditAnywhere, meta=(EditCondition="!LookTwoSidesSeparately", ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0"))
	float Range;
	
	UPROPERTY(EditAnywhere)
	float SpeedRotation;

};
