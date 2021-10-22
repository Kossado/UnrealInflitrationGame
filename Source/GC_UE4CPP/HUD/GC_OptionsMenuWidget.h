#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/InputSettings.h"
//#include "Runtime/UMG/Public/UMG.h"
#include "GC_OptionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGC_OptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGC_OptionsMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void InitializePauseWidget(UWidget*);

	UFUNCTION()
	void Back();

	UFUNCTION()
	void Confirm();

	UFUNCTION()
	void ChangeKeyInteract(FInputChord InputChord);

	UFUNCTION()
	void ChangeKeyInvokeMenu(FInputChord InputChord);

	UFUNCTION()
	void ChangeKeyMoveForward(FInputChord InputChord);

	UFUNCTION()
	void ChangeKeyMoveBack(FInputChord InputChord);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIBack;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIConfirm;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UInputKeySelector* UIActionInteract;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UInputKeySelector* UIActionInvokeMenu;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UInputKeySelector* UIAxisMoveForward;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UInputKeySelector* UIAxisMoveBack;
	
	UWidget* PauseWidget;
	
	UInputSettings* InputSettings;
	TArray<bool> KeyChange;
	
	TArray<struct FInputActionKeyMapping> ActionArrayKeys;
	TArray<struct FInputActionKeyMapping> ActionArrayKeysNext;
	

	TArray<struct FInputAxisKeyMapping> AxisArrayKeys;
	TArray<struct FInputAxisKeyMapping> AxisArrayKeysNext;
};
