// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
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
	UPROPERTY(VisibleAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	AGameCharacter* Character;
	// Character speed for the walk animation
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;
	// Condition for the Win/Defeat dance
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bVictory;
	// Condition for the carry animation
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsCarryingFood;
	
};
