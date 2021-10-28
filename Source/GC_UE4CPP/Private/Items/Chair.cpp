// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Chair.h"

// Sets default values
AChair::AChair():Super()
{
	//Set up Location to sit Component
	SitLocationComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Sit Location")));
	SitLocationComponent->SetupAttachment(RootComponent);
	SetItemProperties(EIS_Immovable);
}

FVector AChair::GetSitLocation()
{
	return SitLocationComponent->GetComponentLocation();
}

FRotator AChair::GetSitRotation()
{
	// return SitLocationComponent->GetComponentRotation() = Crash
	return GetActorRotation() + FRotator(0.f,90.f,0.f);
}

void AChair::Use(AGCCharacter* Character)
{
	if(!bUsed)
	{
		bUsed = true;
		SetItemProperties(EIS_Interacting);
		UserCharacter = Character;
	}
}

void AChair::Free(AGCCharacter* Character)
{
	if(bUsed && UserCharacter == Character)
	{
		UserCharacter = nullptr;
		SetItemProperties(EIS_Immovable);
		bUsed = false;
	}
}

bool AChair::IsUsed()
{
	if(bUsed)
	{
		return true;
	}
	return false;
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
}
