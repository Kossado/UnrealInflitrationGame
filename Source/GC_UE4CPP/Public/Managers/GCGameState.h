#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GCGameState.generated.h"

UENUM()
enum EGameState
{
	EGS_VICTORY,
	EGS_DEFEAT,
	EGS_PAUSE,
	EGS_PLAYING
};

UENUM()
enum ESkinPlayer
{
	EGS_NO_SKIN,
	EGS_KNIGHT,
	EGS_GOBELIN_MALE,
	EGS_GOBELIN_FEMALE,
};

UCLASS()
class GC_UE4CPP_API AGCGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AGCGameState();
	// Current state of the game
	EGameState CurrentGameState;
	// Quantity of food stored in the hideout
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GameData)
	int StoredFood;
	// Quantity of food in the map, excluding those in the hideout
	UPROPERTY(VisibleAnywhere, Category=GameData)
	int PickableFood;
	// Quantity of food needed to win the game
	UPROPERTY(VisibleAnywhere, Category=GameData)
	int StoredFoodToWin;
	// Skin of player
	ESkinPlayer SkinPlayer;

	int PlayerTeamId=0;
};
