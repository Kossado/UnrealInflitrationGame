// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "GameFramework/Actor.h"
#include "SpotFood.generated.h"

class AFoodManager;

UCLASS()
class GC_UE4CPP_API ASpotFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpotFood();
	void Initialize(AFoodManager * FoodManagerSpawner);

	bool StoreFood(AFood * FoodToStore);
	AFood * TakeFood();

	bool HasFood() const;
	bool IsOnGround() const;

	//Return bounds on object on what is landed
	bool GetBoundsSupportFood(FVector& Origin, FVector& BoxExtent);
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AFoodManager * FoodManager= nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> BP_Food;

	AFood * StoredFood= nullptr;
	
};
