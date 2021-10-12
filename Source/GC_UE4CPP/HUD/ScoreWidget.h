// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UScoreWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	void UpdateCurrentFood(int32 value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTCombo;
};
