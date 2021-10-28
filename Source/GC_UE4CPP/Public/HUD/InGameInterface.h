#pragma once

#include "CoreMinimal.h"
#include "GameStatusWidget.h"
#include "OptionsMenuWidget.h"
#include "PauseMenuWidget.h"
#include "ScoreMenuWidget.h"
#include "GameFramework/HUD.h"
#include "InGameInterface.generated.h"

UCLASS()
class GC_UE4CPP_API AInGameInterface : public AHUD
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
	
private:
	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> OptionsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> GameStatusWidgetClass;
	
	UScoreMenuWidget* ScoreWidget;
	UPauseMenuWidget* PauseWidget;
	UOptionsMenuWidget* OptionsWidget;
	UGameStatusWidget* GameStatusWidget;
};