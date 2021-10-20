#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
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

	UFUNCTION()
	void Back();

	UFUNCTION()
	void Confirm();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIBack;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIConfirm;
};
