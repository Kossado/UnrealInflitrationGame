// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIEnemyCharacter.h"

#include "Characters/KnightCharacter.h"
#include "AI/AIEnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
// Sets default values
AAIEnemyCharacter::AAIEnemyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Can't be used in constructor because of "meta = (UnsafeDuringActorConstruction = "true")" in CharacterMovementComponent
	// GetCharacterMovement()->SetAvoidanceEnabled(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
}


// Called when the game starts or when spawned
void AAIEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAIEnemyCharacter::OnHit);

}


// Called to bind functionality to input
void AAIEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemyCharacter::StoreFood(ASpotFood * SpotFood)
{
	if(ItemInHand==nullptr || !ItemInHand->IsA(AFood::StaticClass()) || SpotFood == nullptr)
	{
		return;
	}
	
	AFood * FoodToStore = Cast<AFood>(ItemInHand);

	DropItem();
	
	SpotFood->StoreFood(FoodToStore);
}

void AAIEnemyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	if(!OtherActor->IsA(AKnightCharacter::StaticClass()))
	{
		return;
	}

	AKnightCharacter * PlayerCharacter = Cast<AKnightCharacter>(OtherActor);

	if(PlayerCharacter == nullptr)
	{
		return;
	}
	
	AAIEnemyController * AIEnemyController = Cast<AAIEnemyController>(GetController());

	if(AIEnemyController != nullptr)
	{
		AIEnemyController->HasHitPlayer();
	}
}


