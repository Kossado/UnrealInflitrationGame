// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "ScoreWidget.h"
#include "InGameInterface.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AInGameInterface : public AHUD
{
	GENERATED_BODY()

public:
	AInGameInterface();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Pause();

	UFUNCTION()
		void UpdateCurrentFood(int32 value);

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
		TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
		TSubclassOf<UUserWidget> MenuWidgetClass;
	
private:
	UScoreWidget* ScoreWidget;
	UMenuWidget* MenuWidget;
};
