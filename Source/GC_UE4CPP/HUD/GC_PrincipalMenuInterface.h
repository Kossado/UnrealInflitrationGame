#pragma once

#include "CoreMinimal.h"
#include "GC_MainMenuWidget.h"
#include "GameFramework/HUD.h"
#include "GC_PrincipalMenuInterface.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AGC_PrincipalMenuInterface : public AHUD
{
	GENERATED_BODY()

public:
	AGC_PrincipalMenuInterface();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
	UGC_MainMenuWidget* MainMenuWidget;
};
