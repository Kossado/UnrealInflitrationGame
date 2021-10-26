// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GCCharacter.h"
#include "Interactable.h"
#include "Item.h"
#include "Components/SphereComponent.h"

#include "InteractiveItem.generated.h"

UENUM()
enum EItemState
{
	EIS_Movable,
	EIS_Interacting,
	EIS_Immovable,
	EIS_Disabled
};

UCLASS()
class GC_UE4CPP_API AInteractiveItem : public AItem, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveItem();
	
	void SetItemProperties(EItemState State) const;

	void DisableTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Trigger;
	UPROPERTY(EditAnywhere, Category="Item")
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(EditAnywhere, Category="Item")
	FName ItemName;

	AGCCharacter* Character = nullptr;
	
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	///////////////// INTERFACE IInteractable ///////////////////////
	
public:
	virtual FName GetName() override;
	
	virtual void OnInteract() override;
	
	///////////////// INTERFACE IInteractable ///////////////////////
};
