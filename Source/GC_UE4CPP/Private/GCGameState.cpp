// Fill out your copyright notice in the Description page of Project Settings.


#include "GCGameState.h"

AGCGameState::AGCGameState(): Super(),
CurrentGameState(EGS_PLAYING),
StoredFood(0),
PickableFood(0),
StoredFoodToWin(5)
{
}
