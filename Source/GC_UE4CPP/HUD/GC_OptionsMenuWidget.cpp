#include "GC_OptionsMenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UGC_OptionsMenuWidget::UGC_OptionsMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGC_OptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(UIBack)
	{
		UIBack->OnClicked.AddDynamic(this,&UGC_OptionsMenuWidget::Back);
	}
	if(UIConfirm)
	{
		UIConfirm->OnClicked.AddDynamic(this,&UGC_OptionsMenuWidget::Confirm);
	}
}

void UGC_OptionsMenuWidget::InitializePauseWidget(UWidget* pauseWidget)
{
	PauseWidget = pauseWidget;
}

void UGC_OptionsMenuWidget::Back()
{
	if(UIBack)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGC_OptionsMenuWidget::Confirm()
{
	if(UIConfirm)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	}
}