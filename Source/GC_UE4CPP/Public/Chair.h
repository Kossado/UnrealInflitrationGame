// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "Chair.generated.h"

UCLASS()
class GC_UE4CPP_API AChair : public AInteractiveItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChair();
	
	UFUNCTION()
	FVector GetSitLocation();
	UFUNCTION()
	FRotator GetSitRotation();

	virtual void OnInteract() override;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bUsed = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SitLocationComponent;
};
