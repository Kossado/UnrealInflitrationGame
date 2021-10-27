// import class intern
#include "HUD/GC_ScoreMenuWidget.h"

// Constructor
void UGC_ScoreMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

// Function to update current food in progress bar in score menu widget
void UGC_ScoreMenuWidget::UpdateCurrentFood(int32 value)
{
	if(UIProgression)
	{
		UIProgression->SetPercent(value * 0.20f);
	}
}