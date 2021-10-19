// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chair.h"
#include "Chest.h"
#include "Food.h"
#include "GameFramework/Character.h"
#include "MainGameMode.h"
#include "Components/BoxComponent.h"

#include "GameCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Takes food and carry it
	void CarryFood(AFood* FoodToCarry);
	// Drop food on the ground
	void DropFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Change speed according to the parameters
	void ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator);
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Interact();

	void StoreFood();

	void SitDown();

	void StandUp();
	
private:
	// Collision detection with items
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionMesh;
	// Food to pick = in Overlap
	AFood* FoodToPick = nullptr;
	// Carried food (might be null)
	AFood* CarriedFood = nullptr;
	// Chest to detect = in Overlap
	AChest* ChestInFront = nullptr;
	// Chair to detect in overlap
	AChair* ChairInFront = nullptr;
	bool bIsSitting = false;
	// Characters Speed handfree
	float BaseWalkSpeed;
	// Characters Speed when carrying food
	float CarryWalkSpeedMultiplicator;

	AMainGameMode* MainGameMode;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE AFood* GetCarriedFood() const { return CarriedFood; }
	FORCEINLINE bool IsSitting() const { return bIsSitting; }

};
