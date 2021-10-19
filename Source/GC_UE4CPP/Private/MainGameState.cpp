// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"

AMainGameState::AMainGameState():
CurrentGameState(EGS_PLAYING),
StoredFood(0),
PickableFood(0),
StoredFoodToWin(5),
LaunchGame(true)
{
}
