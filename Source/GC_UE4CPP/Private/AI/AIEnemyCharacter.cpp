// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIEnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIEnemyCharacter::AAIEnemyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Can't be used in constructor because of "meta = (UnsafeDuringActorConstruction = "true")" in CharacterMovementComponent
	// GetCharacterMovement()->SetAvoidanceEnabled(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AAIEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemyCharacter::StoreFood(ASpotFood * SpotFood)
{
	if(CarriedFood==nullptr || SpotFood == nullptr)
	{
		return;
	}
	
	AFood * FoodToStore = CarriedFood;

	Super::DropFood();
	
	SpotFood->StoreFood(FoodToStore);
}

