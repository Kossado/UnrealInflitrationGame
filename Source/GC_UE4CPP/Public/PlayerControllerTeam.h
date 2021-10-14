// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerTeam.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API APlayerControllerTeam : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APlayerControllerTeam();

private:
	FGenericTeamId TeamId;
	FGenericTeamId GetGenericTeamId() const;
	
};
