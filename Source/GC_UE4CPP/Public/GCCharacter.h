// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCGameMode.h"
#include "Interactable.h"

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
	void GrabItem(class AInteractiveItem* InteractiveItem);
	// Drop an item
	void DropItem();
	// Drop food on the ground
	void StoreItem();
	//void DropFood();
	virtual void SitDown();

	virtual void StandUp();
	void OnEnterActor(AActor* InteractiveActor);
	void OnLeaveActor(AActor* InteractiveActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Change speed according to the parameters
	void ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator);

	AActor* CurrentInteractiveActor;
	IInteractable* CurrentInteractive;
	
private:
	/*// Food to pick = in Overlap
	AFood* FoodToPick = nullptr;
	// Carried food (might be null)
	AFood* CarriedFood = nullptr;
	// Chest to detect = in Overlap
	AChest* ChestInFront = nullptr;
	// Chair to detect in overlap
	AChair* ChairInFront = nullptr;*/
	bool bSit = false;
	// Characters Speed handfree
	float BaseWalkSpeed;
	// Characters Speed when carrying food
	float CarryWalkSpeedMultiplicator;
	// Grabbed item
	AInteractiveItem* ItemInHand = nullptr;

	AGCGameMode* LevelGameMode;
	bool bHasItem = false;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//FORCEINLINE AFood* GetCarriedFood() const { return CarriedFood; }
	FORCEINLINE bool IsSitting() const { return bSit; }
	FORCEINLINE bool HasItem() const { return bHasItem; }

};
