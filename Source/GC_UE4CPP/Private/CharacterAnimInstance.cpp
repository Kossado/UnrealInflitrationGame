// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "Hero.h"
#include "IACharacter.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AGameCharacter>(TryGetPawnOwner());
	bIsCarryingFood = false;
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Character == nullptr)
	{
		Character = Cast<AGameCharacter>(TryGetPawnOwner());// Double check - Useless ?
	}
	if(Character)
	{
		FVector Velocity = Character->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();
		if(Character->IsA(AHero::StaticClass()))
		{
			// if GameState = Victory Then bVictory = true;
			// if GameState = Defeat Then bVictory = false;
			// if GameState = InProgress Then bGameFinished = false
		}
		if(Character->IsA(AIACharacter::StaticClass()))
		{
			// Check Victory and Defeat condition for IA
		}
		if(Character->GetCarriedFood() != nullptr)
		{
			bIsCarryingFood = true;
		}
		else
		{
			bIsCarryingFood = false;
		}
	}
}
