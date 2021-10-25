// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "SpotFood.h"
#include "GameFramework/Actor.h"
#include "FoodManager.generated.h"

UCLASS()
class GC_UE4CPP_API AFoodManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodManager();

	UFUNCTION(CallInEditor)
	void SpawnFoodSpot();

	UFUNCTION(CallInEditor)
	void RemoveFoodSpot(ASpotFood* SpotFood);

	int GetMaxFoodInScene() const;
	bool IsRemainingSlotFood() const;
	int GetCurrentNbFoodInScene() const;

	void RemoveFoodInCounterFoodScene(AFood * FoodToIgnore);
	void DestroyFood(AFood * FoodToDestroy);
	AFood * SpawnFood();
	AFood * SpawnFood(FTransform SpawnTranform);

	ASpotFood * GetRandomSpotFood(TArray<ASpotFood*> ListSpotFoodToIgnore={});

	void StoreFood(ASpotFood * SpotFood, AFood * FoodToStore);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int NbFoodSpawnedBeginPlay=1;
	
	UPROPERTY(EditAnywhere)
	TArray<ASpotFood*> ListSpotFood;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpotFood> BP_SpotFood;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> BP_Food;

	UPROPERTY(EditAnywhere)
	int MaxFoodInScene = 5;
	
	TArray<AFood*> ListExistingFood;
	
};
