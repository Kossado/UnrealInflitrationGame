// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Item.h"
#include "Components/SphereComponent.h"

#include "InteractiveItem.generated.h"


UCLASS()
class GC_UE4CPP_API AInteractiveItem : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveItem();
	virtual void SetItemProperties(EItemState State) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Trigger;

	// Called to disable trigger collisions
	void DisableTrigger();
	// Called to enable trigger collisions
	void EnableTrigger();

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
