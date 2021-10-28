#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStatusWidget.generated.h"

UCLASS()
class GC_UE4CPP_API UGameStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void PlayAgain();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void QuitDesktop();

	UFUNCTION()
	void QuitMainMenu();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIPlayAgain;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuitDesktop;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIQuitMainMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* UITitreVictory;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* UITitreDefeat;
};