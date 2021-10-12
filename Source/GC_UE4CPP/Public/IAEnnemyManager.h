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
	TSubclassOf<AIAEnnemyCharacterController> BP_ControllerIA;
	
	virtual void SpawnPawn();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UnSpawnIA(AIAEnnemyCharacterController* UnSpawnIA); 

};
