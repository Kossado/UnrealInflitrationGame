// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Food.generated.h"

UENUM()
enum EFoodState
{
	EFS_PickedUp,
	EFS_Dropped
};

UCLASS()
class GC_UE4CPP_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Setting up item properties for each states
	void SetFoodProperties(EFoodState State);	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	EFoodState FoodState;

public:
	FORCEINLINE EFoodState GetFoodState() const { return FoodState;}
	void SetFoodState(EFoodState State);
	FORCEINLINE UStaticMeshComponent* GetFoodMesh() const {return StaticMesh;}
	
};
