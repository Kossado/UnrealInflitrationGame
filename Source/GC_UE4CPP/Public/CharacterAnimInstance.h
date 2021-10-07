// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
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
	UPROPERTY(VisibleAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	ACharacter* Character;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bVictory;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bDefeat;
	
};
