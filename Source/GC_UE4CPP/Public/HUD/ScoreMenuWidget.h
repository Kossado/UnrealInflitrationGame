#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreMenuWidget.generated.h"

UCLASS()
class GC_UE4CPP_API UScoreMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateCurrentFood(int32 value);

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* UIProgression;
};
