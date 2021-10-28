// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food/FoodManager.h"
#include "Food/SpotFood.h"
#include "GameFramework/Actor.h"
#include "AIEnemyCharacter.h"
#include "AIPatrolPoint.h"
#include "Characters/LinkSkeletalMeshAnimation.h"
#include "AIEnemyManager.generated.h"


class AAIEnemyController;

UCLASS()
class GC_UE4CPP_API AAIEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIEnemyManager();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE AAIPatrolPoint * GetUnSpawnPoint() const { return UnSpawnAIPatrolPoint; }
	void UnSpawnAI(AAIEnemyController* UnSpawnAI);
	void UnSpawnAIAndPrepareRespawn(AAIEnemyController* UnSpawnAI);

	AFoodManager * GetFoodManager() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	 AFoodManager * FoodManager = nullptr;
	
	
	UPROPERTY(EditAnywhere)
	AAIPatrolPoint* SpawnAIPatrolPoint = nullptr;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAIEnemyCharacter> BP_CharacterAI;
		
	UPROPERTY(EditAnywhere)
		unsigned int NbRetriesSpotBeforeBack=2;

	UPROPERTY(EditAnywhere)
	int NbAIStartingGame=2;

	UPROPERTY(EditAnywhere)
	int TimeToPop3rdAI=60;

	UPROPERTY(EditAnywhere)
	unsigned int TimeMinBetweenRepopAI=0;
	
	UPROPERTY(EditAnywhere)
	unsigned int TimeMaxBetweenRepopAI=5;

	TArray<AAIEnemyController*> ListAIControllerOnScene;

	UPROPERTY(EditAnywhere)
	AAIPatrolPoint* UnSpawnAIPatrolPoint = nullptr;

	virtual void SpawnPawn();

	void SpawnAIRandomTime(int TimeMin, int TimeMax);

	int EnemyTeamId=1;
	TArray<LinkSkeletalMeshAnimation> SkeletalMeshesWithAnimation;
	
};
