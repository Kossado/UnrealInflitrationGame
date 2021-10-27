#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PrincipalMenuWidget.generated.h"

UCLASS()
class GC_UE4CPP_API UPrincipalMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
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
