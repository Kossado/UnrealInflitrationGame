// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Chest.h"
#include "Items/PickableItem.h"
#include "GameFramework/Character.h"
#include "GCCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AGCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGCCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void GrabItem(class APickableItem* PickableItem);
	void DropItem();
	virtual void SitDown(class AChair* Chair);
	virtual void StandUp();
	// Add InteractiveActor to the InteractiveActors List
	void OnEnterActor(AInteractiveItem* InteractiveActor);
	// Remove InteractiveActor from the InteractiveActors List
	void OnLeaveActor(AInteractiveItem* InteractiveActor);
	void BeginRotate();
	void EndRotate();
	bool IsRotating() const;
	// Remove character's possessions
	void UnSpawn();

	FORCEINLINE const USkeletalMeshSocket * GetSocketBaseCharacter() const { return SocketBaseCharacter; }
	FORCEINLINE FVector GetSocketBaseCharacterLocation() const { return GetMesh()->GetSocketLocation(NameSocketBaseCharacter); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Change speed according to the parameters
	void ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator);
	// TArray of InteractiveItems in range
	TArray<AInteractiveItem*> InteractiveItems;
	APickableItem* ItemInHand = nullptr;
	bool bCarryItem = false;
	bool bSit = false;
	AChair* ChairUsed = nullptr;
	// Characters Speed handfree

	float BaseWalkSpeed;

	//Socket which represent the character on the ground. By Example, the middle between two feet
	UPROPERTY(EditAnywhere)
	FName NameSocketBaseCharacter;

	const USkeletalMeshSocket * SocketBaseCharacter = nullptr;


private:
	// Characters Speed when carrying food
	UPROPERTY(EditAnywhere)
	float CarryWalkSpeedMultiplicator=0.5f;
	bool bRotate =false;

public:	
	FORCEINLINE bool IsSitting() const { return bSit; }
	FORCEINLINE bool HasItem() const { return bCarryItem; }

};
