// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "MainGameMode.h"
#include "Animation/AnimInstance.h"

#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	// Character's ref
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	AGameCharacter* Character;
	// Character speed for the walk animation
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	float Speed;
	// Condition for the Victory/Defeat dance
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bVictory;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bGameInProgress;
	// Condition for the carry animation
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bIsCarryingFood;
	
	AMainGameMode* MainGameMode;
	
};
