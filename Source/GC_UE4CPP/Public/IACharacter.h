// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "IACharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AIACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIACharacter(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual bool Initialize(AIA_Manager * AIManager);
};
