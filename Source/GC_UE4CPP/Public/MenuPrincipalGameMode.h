#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GC_UE4CPP/HUD/GC_PrincipalMenuInterface.h"
#include "MenuPrincipalGameMode.generated.h"

UCLASS()
class GC_UE4CPP_API AMenuPrincipalGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMenuPrincipalGameMode();
	
	virtual void StartPlay() override;

	AGC_PrincipalMenuInterface* PrincipalMenuInterface;
};
