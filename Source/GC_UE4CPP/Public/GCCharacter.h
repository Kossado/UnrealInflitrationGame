// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chest.h"
#include "PickableItem.h"
#include "GameFramework/Character.h"
#include "GCCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AGCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGCCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Takes food and carry it
	//void CarryFood(AFood* FoodToCarry);
	// Grab an item
	void GrabItem(class APickableItem* PickableItem);
	// Drop an item
	void DropItem();
	//void DropFood();
	virtual void SitDown(class AChair* Chair);

	virtual void StandUp();
	void OnEnterActor(AInteractiveItem* InteractiveActor);
	void OnLeaveActor(AInteractiveItem* InteractiveActor);

	
	void BeginRotate();
	void EndRotate();
	bool IsRotating() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Change speed according to the parameters
	void ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator);

	TArray<AInteractiveItem*> InteractiveItems;
	/*AActor* CurrentInteractiveActor;
	IInteractable* CurrentInteractive;*/
	APickableItem* ItemInHand = nullptr;

	bool bHasItem = false;
	bool bSit = false;
	AChair* ChairUsed = nullptr;
	// Characters Speed handfree
	float BaseWalkSpeed;

private:
	/*// Food to pick = in Overlap
	AFood* FoodToPick = nullptr;
	// Carried food (might be null)
	AFood* CarriedFood = nullptr;
	// Chest to detect = in Overlap
	AChest* ChestInFront = nullptr;
	// Chair to detect in overlap
	AChair* ChairInFront = nullptr;*/

	// Characters Speed when carrying food
	float CarryWalkSpeedMultiplicator;

	bool bRotate =false;

	
public:	
	//FORCEINLINE AFood* GetCarriedFood() const { return CarriedFood; }
	FORCEINLINE bool IsSitting() const { return bSit; }
	FORCEINLINE bool HasItem() const { return bHasItem; }

};
