// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCCharacter.h"
#include "Managers/GCGameMode.h"
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
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	AGCCharacter* Character = nullptr;
	// Character speed for the walk animation
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	float Speed = 0.f;
	// Condition for the Victory/Defeat animation
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bVictory = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bGameInProgress = true;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bCarryItem = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bSit = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,meta = (AllowPrivateAccess = "true"))
	bool bRotate = false;
	
	AGCGameMode* GameMode = nullptr;

	void CheckWalkAnimation();
	void CheckWinOrDefeatAnimation();

	
	
};
