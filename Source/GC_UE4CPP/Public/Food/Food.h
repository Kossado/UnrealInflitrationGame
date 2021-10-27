// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PickableItem.h"

#include "Food.generated.h"

UCLASS()
class GC_UE4CPP_API AFood : public APickableItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();
	
	bool IsOnGround() const;
	bool GetBoundsSupportFood(FVector& Origin, FVector& BoxExtent);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
