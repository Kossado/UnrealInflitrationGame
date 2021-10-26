// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood():Super()
{
	SetItemProperties(EIS_Movable);
}

void AFood::OnInteract()
{
	Super::OnInteract();
	if(Character != nullptr)
	{
		if(!Character->HasItem())
		{
			Character->GrabItem(this);
		}
		else
		{
			Character->DropItem();
		}
	}
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
}