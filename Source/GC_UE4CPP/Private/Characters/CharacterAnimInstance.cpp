// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterAnimInstance.h"

#include "AI/AIEnemyCharacter.h"
#include "Managers/GCGameMode.h"
#include "Characters/KnightCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MainGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Character = Cast<AGCCharacter>(TryGetPawnOwner());
	bCarryItem = false;
	bGameInProgress = true;
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Character == nullptr)
	{
		Character = Cast<AGCCharacter>(TryGetPawnOwner());// Double check - Useless ?
	}
	if(Character)
	{
		FVector Velocity = Character->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();
		if(Character->IsA(AKnightCharacter::StaticClass()) && MainGameMode)
		{
			if(MainGameMode->GetCurrentGameState() == EGS_VICTORY)
			{
				bVictory = true;
				bGameInProgress = false;
			}else if(MainGameMode->GetCurrentGameState() == EGS_DEFEAT)
			{
				bVictory = false;
				bGameInProgress = false;
			}
		}
		if(Character->IsA(AAIEnemyCharacter::StaticClass()) && MainGameMode)
		{
			if(MainGameMode->GetCurrentGameState() == EGS_VICTORY)
			{
				bVictory = false;
				bGameInProgress = false;
			}else if(MainGameMode->GetCurrentGameState() == EGS_DEFEAT)
			{
				bVictory = true;
				bGameInProgress = false;
			}
		}
		if(Character->HasItem())
		{
			bCarryItem = true;
		}
		else
		{
			bCarryItem = false;
		}
		if(Character->IsSitting())
		{
			bSit = true;
		}else
		{
			bSit = false;
		}

		if(Character->IsRotating())
		{
			bRotate = true;
		}

		else
		{
			bRotate = false;
		}
		
	}
}