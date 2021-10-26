// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InteractiveItem.h"

#include "Food.generated.h"

UCLASS()
class GC_UE4CPP_API AFood : public AInteractiveItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

	virtual void OnInteract() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};