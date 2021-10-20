#include "GC_ScoreMenuWidget.h"

UGC_ScoreMenuWidget::UGC_ScoreMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGC_ScoreMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGC_ScoreMenuWidget::UpdateCurrentFood(int32 value)
{
	if(UIProgression)
	{
		UIProgression->SetPercent(value * 0.20f);
	}
}