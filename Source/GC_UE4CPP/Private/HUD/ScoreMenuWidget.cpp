// Import intern class
#include "HUD/ScoreMenuWidget.h"

// Import extern class
#include "Runtime/UMG/Public/UMG.h" // For UProgressBar

// Constructor
void UScoreMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

// Function to update current food in progress bar in score menu widget
void UScoreMenuWidget::UpdateCurrentFood(int32 value)
{
	if(UIProgression)
	{
		UIProgression->SetPercent(value * 0.20f);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UScoreMenuWidget::UpdateCurrentFood - UIProgression null"));
	}
}