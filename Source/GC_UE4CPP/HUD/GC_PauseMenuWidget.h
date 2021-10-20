#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "GC_PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGC_PauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGC_PauseMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void QuitDesktop();

	UFUNCTION()
	void QuitMainMenu();

	UFUNCTION()
	void Options();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIResume;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIRestart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuitDesktop;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuitMainMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIOptions;
};
