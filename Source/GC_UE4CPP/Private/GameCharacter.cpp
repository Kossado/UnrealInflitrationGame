// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGameCharacter::AGameCharacter():
BaseWalkSpeed(300.f),
CarryWalkSpeedMultiplicator(0.5f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set Maximum movement speed of the character
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacter::CarryFood(AFood* FoodToCarry)
{
	if(FoodToCarry)
	{
		FoodToCarry->SetFoodState(EFoodState::EFS_PickedUp);
		//Get the Hand Socket
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("HandSocket"));
		if(HandSocket)
		{
			// Attach food to the hand socket
			HandSocket->AttachActor(FoodToCarry,GetMesh());
		}
		CarriedFood = FoodToCarry;
		ChangeCharacterSpeed(BaseWalkSpeed, CarryWalkSpeedMultiplicator);
	}
}

void AGameCharacter::ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator)
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewSpeed * SpeedMultiplicator;
	}
}

void AGameCharacter::DropFood()
{
	if(CarriedFood)
	{
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		CarriedFood->GetFoodMesh()->DetachFromComponent(DetachmentTransformRules);
		CarriedFood->SetFoodState(EFoodState::EFS_Dropped);
		CarriedFood = nullptr;
		ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
	}
}

