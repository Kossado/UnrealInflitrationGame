// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIResume;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIRestart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuit;
};
