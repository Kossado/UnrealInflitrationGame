// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chair.h"
#include "Chest.h"
#include "Food/Food.h"
#include "GameFramework/Character.h"
#include "GCGameMode.h"
#include "Components/BoxComponent.h"

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

	bool IsCarryingFood() const;
	
	// Takes food and carry it
	void CarryFood(AFood* FoodToCarry);
	// Drop food on the ground
	void DropFood();

	void BeginRotate();
	void EndRotate();
	bool IsRotating() const;

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

	UFUNCTION()
	virtual void SitDown();

	UFUNCTION()
	virtual void StandUp();

	
	
private:
	// Collision detection with items
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionMesh;
	// Food to pick = in Overlap
	UPROPERTY()
	AFood* FoodToPick = nullptr;
	// Carried food (might be null)
	UPROPERTY()
	AFood* CarriedFood = nullptr;
	// Chest to detect = in Overlap
	UPROPERTY()
	AChest* ChestInFront = nullptr;
	// Chair to detect in overlap
	UPROPERTY()
	AChair* ChairInFront = nullptr;
	UPROPERTY()
	bool bIsSitting = false;
	// Characters Speed handfree
	float BaseWalkSpeed;
	// Characters Speed when carrying food
	float CarryWalkSpeedMultiplicator;

	bool bRotate = false;

	AGCGameMode* MainGameMode;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE AFood* GetCarriedFood() const { return CarriedFood; }
	FORCEINLINE bool IsSitting() const { return bIsSitting; }

};
