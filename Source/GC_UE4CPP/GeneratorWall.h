// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratorWall.generated.h"

UENUM()
enum Axe
{
	AxeX UMETA(DisplayName = "Axe X"),
	AxeY UMETA(DisplayName = "Axe Y"),
	AxeZ UMETA(DisplayName = "Axe Z"),
};

UCLASS()


class GC_UE4CPP_API AGeneratorWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorWall();

	UPROPERTY(EditAnywhere)
	int NumberWallX;

	UPROPERTY(EditAnywhere)
	int NumberWallY;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* WallPrefab;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	USceneComponent* SceneComponent;
	
	void CreateWall(FVector positionDepart);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
	void CreateWallFromEditor();
	
	void CreateWallFromPlay();
	
};
