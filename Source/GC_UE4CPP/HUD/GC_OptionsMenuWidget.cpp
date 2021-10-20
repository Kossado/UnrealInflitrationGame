// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_OptionsMenuWidget.h"

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