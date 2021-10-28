// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/GCCharacter.h"
#include "Food/SpotFood.h"
#include "AIEnemyCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AAIEnemyCharacter : public AGCCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree = nullptr;

	void StoreFood(ASpotFood * SpotFood);
	void Defeat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()    
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	UCharacterMovementComponent * CharacterMovement = nullptr;
	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
