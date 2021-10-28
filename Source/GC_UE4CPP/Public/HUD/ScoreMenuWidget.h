#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreMenuWidget.generated.h"

UCLASS()
class GC_UE4CPP_API UScoreMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void UpdateCurrentFood(int32 value);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* UIProgression;
};
