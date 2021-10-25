// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

// Sets default values
AChair::AChair()
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

void AChair::OnInteract()
{
	Super::OnInteract();
	if(Character != nullptr)
	{
		if(bUsed)
		{
			SetItemProperties(EIS_Immovable);
			Character->StandUp();
		}
		else
		{
			SetItemProperties(EIS_Interacting);
			Character->SitDown();
		}
		
	}
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
}
