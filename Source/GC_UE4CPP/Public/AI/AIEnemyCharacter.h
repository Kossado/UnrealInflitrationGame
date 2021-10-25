// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "AIEnemyCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AAIEnemyCharacter : public AGCCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree;

	void StoreFood(ASpotFood * SpotFood);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	UCharacterMovementComponent * CharacterMovement;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
