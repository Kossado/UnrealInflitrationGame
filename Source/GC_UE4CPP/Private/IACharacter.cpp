// Fill out your copyright notice in the Description page of Project Settings.


#include "IACharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AIACharacter::AIACharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// if(GetCharacterMovement() != nullptr)
	// {
	// 	GetCharacterMovement()->SetAvoidanceEnabled(true);
	// }
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIACharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

