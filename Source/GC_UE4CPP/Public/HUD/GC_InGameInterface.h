#pragma once

#include "CoreMinimal.h"
#include "GameStatusWidget.h"
#include "GC_OptionsMenuWidget.h"
#include "GC_PauseMenuWidget.h"
#include "GC_ScoreMenuWidget.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "GC_InGameInterface.generated.h"

UCLASS()
class GC_UE4CPP_API AGC_InGameInterface : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION()
		void Pause();

	UFUNCTION()
		void EndGame(bool GameStatus);
	
	UFUNCTION()
		void UpdateCurrentFood(int32 value);

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> OptionsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> GameStatusWidgetClass;
	
private:
	UGC_ScoreMenuWidget* ScoreWidget;
	UGC_PauseMenuWidget* MenuWidget;
	UGC_OptionsMenuWidget* OptionsWidget;
	UGameStatusWidget* GameStatusWidget;
};