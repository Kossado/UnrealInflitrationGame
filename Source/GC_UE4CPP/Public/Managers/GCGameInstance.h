#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers/GCGameState.h"
#include "GCGameInstance.generated.h"

UCLASS()
class GC_UE4CPP_API UGCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGCGameInstance();
	
	ESkinPlayer GetSkinPlayer() const;
	void SetSkinPlayer(ESkinPlayer SkinPlayer);
	
	// Skin of player
	ESkinPlayer SkinPlayer;
};
