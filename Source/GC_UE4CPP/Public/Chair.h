// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.generated.h"

UCLASS()
class GC_UE4CPP_API AChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChair();
	
	UFUNCTION()
	FVector GetSitLocation();
	UFUNCTION()
	FRotator GetSitRotation();

	void SetCollisionProperties(bool bUsed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SitLocationComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
