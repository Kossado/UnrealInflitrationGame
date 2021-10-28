// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterAnimInstance.h"

#include "AI/AIEnemyCharacter.h"
#include "Managers/GCGameMode.h"
#include "Characters/KnightCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Character = Cast<AGCCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Character != nullptr && GameMode != nullptr)
	{
		CheckWalkAnimation();
		CheckWinOrDefeatAnimation();
		bCarryItem = Character->HasItem() ? true : false;
		bSit = Character->IsSitting() ? true : false;
		bRotate = Character->IsRotating() ? true : false;
		
	}
}

void UCharacterAnimInstance::CheckWalkAnimation()
{
	// Update speed value based on the character velocity, if speed > 0 = walk animation
	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();
}

void UCharacterAnimInstance::CheckWinOrDefeatAnimation()
{
	if(Character->IsA(AKnightCharacter::StaticClass()))
	{
		if(GameMode->GetCurrentGameState() == EGS_VICTORY)
		{
			bVictory = true;
			bGameInProgress = false;
		}else if(GameMode->GetCurrentGameState() == EGS_DEFEAT)
		{
			bVictory = false;
			bGameInProgress = false;
		}
	}
	if(Character->IsA(AAIEnemyCharacter::StaticClass()))
	{
		if(GameMode->GetCurrentGameState() == EGS_VICTORY)
		{
			bVictory = false;
			bGameInProgress = false;
		}else if(GameMode->GetCurrentGameState() == EGS_DEFEAT)
		{
			bVictory = true;
			bGameInProgress = false;
		}
	}
}
