#pragma once

#include "CoreMinimal.h"
#include "ChooseHeroMenuWidget.h"
#include "PrincipalMenuWidget.h"
#include "GameFramework/HUD.h"
#include "PrincipalMenuInterface.generated.h"

UCLASS()
class GC_UE4CPP_API APrincipalMenuInterface : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:
	UPrincipalMenuWidget* MainMenuWidget;
	UChooseHeroMenuWidget* ChooseHeroMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> ChooseHeroMenuWidgetClass;
};
