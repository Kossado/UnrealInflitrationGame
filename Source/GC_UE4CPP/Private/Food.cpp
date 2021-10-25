// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
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
			SetItemProperties(EIS_Interacting);
			Character->GrabItem(this);
		}
	}
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
}