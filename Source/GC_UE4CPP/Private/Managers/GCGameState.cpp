#include "Managers/GCGameState.h"

AGCGameState::AGCGameState(): Super(),
CurrentGameState(EGS_PLAYING),
StoredFood(0),
PickableFood(0),
StoredFoodToWin(5),
SkinPlayer(EGS_NO_SKIN)
{
}
