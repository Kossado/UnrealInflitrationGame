#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "GC_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGC_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGC_MainMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Play();

	UFUNCTION()
	void Quit();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIPlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuit;
};
