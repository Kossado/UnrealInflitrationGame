// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemyCharacter.h"
#include "AIController.h"
#include "Food/SpotFood.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIEnemyController.generated.h"


class AAIEnemyManager;

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AAIEnemyController(const FObjectInitializer & ObjectInitializer = FObjectInitializer::Get());
	
	bool Initialize(AAIEnemyManager* AIEnemyManagerSpawner, unsigned int NbRetriesBeforeBackUnSpawn);
	bool IsSpotHasFood();
	void WillNeedNewDestination();
	void SetNextTargetSpotFood(ASpotFood * NextSpotFoodTarget);
	
	AAIEnemyManager* GetAIEnemyManager() const;

	//We override the basic function because the parent function compare this AI controller with actor seen (here it's AI Character)
	//So we go get the controller of this actor and thus compare the both controllers with have both an TeamID while AICharacter doesn't have one
	//and return neutral team if we compare with AICharacter
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	void ForgetTarget();

	bool IsCarryingFood() const;
	void CarryFood(AFood * FoodToCarry);
	bool PutFoodAtStand();
	void DropFood();

	void BeginRotation() const;
	void Rotate(FRotator NextRotation) const;
	void EndRotation() const;
	
	UFUNCTION()
	void SightPlayer(AActor* UpdateActor, FAIStimulus FaiStimulus);

	FORCEINLINE ASpotFood * GetCurrentSpotFoodTarget() const { return CurrentSpotFoodTarget; }
	FORCEINLINE TArray<ASpotFood *> GetListAlreadyCheckedSpotFood() const { return ListSpotFoodAlreadyChecked; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	UBehaviorTreeComponent * BehaviorComponent;
	
	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamID;
	
	unsigned int NbRetriesBeforeBack;
	AAIEnemyManager* AIEnemyManager;

	AActor* TargetChased;
	FVector LastLocationSeenTarget;
	FVector LastDirectionSeenTarget;

	ASpotFood * CurrentSpotFoodTarget;
	TArray<ASpotFood*>  ListSpotFoodAlreadyChecked;

	FTimerHandle OutHandle;
	float CurrentAngle;

	AAIEnemyCharacter * AICharacter;

	bool bCarryFood;
	AFood * AttributedFood;
	
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AI_PerceptionComponent;

};
