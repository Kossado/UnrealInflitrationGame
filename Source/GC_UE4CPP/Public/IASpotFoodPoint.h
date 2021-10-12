// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAPatrolPoint.h"
#include "IASpotFoodPoint.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AIASpotFoodPoint : public AIAPatrolPoint
{
	GENERATED_BODY()

public:
	bool GetFoodState() const;
	void SetFoodState(bool NewStateFood);
	
private:
	bool HasFood;
};
