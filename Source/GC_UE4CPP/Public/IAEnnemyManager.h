// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IASpotFoodPoint.h"
#include "GameFramework/Actor.h"

#include "IAPawnManager.h"
#include "IAEnnemyManager.generated.h"

class AIAEnnemyCharacterController;
class AIACharacter;

UCLASS()
class GC_UE4CPP_API AIAEnnemyManager : public AIAPawnManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIAEnnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	AIAPatrolPoint* SpawnAIPatrolPoint;
	
	UPROPERTY(EditAnywhere)
		TArray<AIASpotFoodPoint*> ListSpotFood;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AIACharacter> BP_CharacterIA;

	UPROPERTY(EditAnywhere)
		unsigned int NbRetriesSpotBeforeBack=2;

	UPROPERTY(EditAnywhere)
	int NbIAStartingGame=2;

	UPROPERTY(EditAnywhere)
	int TimeToPop3rdIA=60;

	UPROPERTY(EditAnywhere)
	unsigned int TimeMinBetweenRepopIA=0;
	
	UPROPERTY(EditAnywhere)
	unsigned int TimeMaxBetweenRepopIA=5;

	TArray<AIAEnnemyCharacterController*> ListIAControllerOnScene;

	
	virtual void SpawnPawn();

	void SpawnIARandomTime(int TimeMin, int TimeMax);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UnSpawnIA(AIAEnnemyCharacterController* UnSpawnIA);
	void UnSpawnIAAndPrepareRespawn(AIAEnnemyCharacterController* UnSpawnIA);
	
};
