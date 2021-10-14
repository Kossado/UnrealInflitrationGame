// Fill out your copyright notice in the Description page of Project Settings.


#include "IASpotFoodPoint.h"

bool AIASpotFoodPoint::GetFoodState() const
{
	return HasFood;
}
void AIASpotFoodPoint::SetFoodState(const bool NewStateFood)
{
	HasFood = NewStateFood;
}