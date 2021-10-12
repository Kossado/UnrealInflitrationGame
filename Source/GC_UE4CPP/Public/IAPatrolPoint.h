// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IAPatrolPoint.generated.h"

UCLASS()
class GC_UE4CPP_API AIAPatrolPoint : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AIAPatrolPoint();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
