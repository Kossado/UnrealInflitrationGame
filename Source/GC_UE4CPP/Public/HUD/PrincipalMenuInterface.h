#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditDefaultsOnly, Category=Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
	UPrincipalMenuWidget* MainMenuWidget;
};
