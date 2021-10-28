// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickableItem.h"

APickableItem::APickableItem():Super()
{
}

void APickableItem::GrabItem()
{
	SetItemProperties(EIS_Interacting);
}

void APickableItem::DestroyItem()
{
	Destroy();
}

void APickableItem::DropItem()
{
	SetItemProperties(EIS_Movable);
}

void APickableItem::DisableItem()
{
	SetItemProperties(EIS_Disabled);
}
