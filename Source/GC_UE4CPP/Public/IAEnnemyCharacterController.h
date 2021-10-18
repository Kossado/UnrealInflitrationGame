// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAPawnController.h"
#include "IASpotFoodPoint.h"
#include "Perception/AISenseConfig_Sight.h"
#include "IAEnnemyCharacterController.generated.h"


class AIAEnnemyManager;

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AIAEnnemyCharacterController : public AIAPawnController
{
	GENERATED_BODY()

public:

	AIAEnnemyCharacterController(const FObjectInitializer & ObjectInitializer);
	
	bool Initialize(AIAEnnemyManager* IAEnnemyManagerSpawner, TArray<AIASpotFoodPoint *> ListSpotFoodsPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint, unsigned int NbRetriesBeforeBackUnSpawn);
	void SetNextTargetAIPatrolPoint(AIASpotFoodPoint * NextTargetAIPatrolPoint);
	bool IsSpotHasFood(AIASpotFoodPoint * SpotFood);
	void WillNeedNewDestination();

	AIAEnnemyManager* GetIAEnnemyManager() const;

	//We override the basic function because the parent function compare this IA controller with actor seen (here it's IA Character)
	//So we go get the controller of this actor and thus compare the both controllers with have both an TeamID while IACharacter doesn't have one
	//and return neutral team if we compare with IACharacter
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	void ForgetTarget();
	
	UFUNCTION()
	void SightPlayer(AActor* UpdateActor, FAIStimulus FaiStimulus);
	// void SightPlayer(const TArray<AActor*>& UpdateActors);
private:

	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamID;
	
	unsigned int NbRetriesBeforeBack;
	AIAEnnemyManager* IAEnnemyManager;

	AActor* TargetChased;
	FVector LastLocationSeenTarget;
	FVector LastDirectionSeenTarget;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AI_PerceptionComponent;

};
