// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCCharacter.h"
#include "GCGameMode.h"
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
	AGCCharacter* Character;
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
	bool bCarryItem;
	// Condition to sit in chair
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bSit;
	
	AGCGameMode* MainGameMode;
	
};
