// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Chest.h"

#include "Managers/GCGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChest::AChest():Super()
{
	// Setup food position in chest
	FoodPlaceholder.Init(nullptr,5);
	for(int i = 0; i < FoodPlaceholder.Num();i++)
	{
		FString Name = TEXT("FoodPlaceholder");
		Name.Append(FString::FromInt(i));
		FoodPlaceholder[i] = CreateDefaultSubobject<USceneComponent>(FName(Name));
		FoodPlaceholder[i]->SetupAttachment(RootComponent);
		FoodPlaceholder[i]->SetRelativeLocation(FVector(i*20,0.f,0.f));
	}
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	SetItemProperties(EIS_Immovable);	
}

FVector AChest::GetValidStoredPosition()
{
	AGCGameMode* MainGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(MainGameMode)
	{
		int Index = MainGameMode->GetStoredFood();
		if(FoodPlaceholder.IsValidIndex(Index))
			return FoodPlaceholder[Index]->GetComponentLocation();
	}
	return GetActorLocation();
}

FRotator AChest::GetValidStoredRotation()
{
	AGCGameMode* MainGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(MainGameMode)
	{
		int Index = MainGameMode->GetStoredFood();
		if(FoodPlaceholder.IsValidIndex(Index))
			return FoodPlaceholder[Index]->GetComponentRotation();
	}
	return GetActorRotation();
}

