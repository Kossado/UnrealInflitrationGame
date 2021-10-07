// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPatrolPoint.h"
#include "IACharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MyIAController.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMyIAController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		AIACharacter * CharacterControlled;

	UPROPERTY(EditAnywhere)
	UBehaviorTreeComponent * BehaviorComponent;

	UPROPERTY(EditAnywhere)
	UBlackboardComponent * BlackboardComponent;


	// Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGoKey; // Location/point for the AI to go to

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey; // reference to the players location

	
	public:
	AMyIAController (const FObjectInitializer & ObjectInitializer);

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	void SetNextTargetAIPatrolPoint(AActor * NextTargetAIPatrolPoint);
	AActor * GetRandomAIPatrolPoint(bool ExcludeCurrentPosition);
	
	protected:
		virtual void OnPossess(APawn* InPawn) override;
		virtual void OnUnPossess() override;

	private:
		TArray<AActor*> PatrolPoints;
		int CurrentPatrolPoints=-1;

};
