// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/FoodManager.h"

#include "Food/SpotFood.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GCGameMode.h"

// Sets default values
AFoodManager::AFoodManager() : Super()
{

}


// Called when the game starts or when spawned
void AFoodManager::BeginPlay()
{
	Super::BeginPlay();

	MainGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MainGameMode != nullptr)
	{
		MainGameMode->FoodManager = this;
	}
}

void AFoodManager::Initialize()
{
	for(ASpotFood * SpotFood : ListSpotFood)
	{
		SpotFood->Initialize(this);
	}
	
	TArray<ASpotFood *> ListSpotFoodAlreadyBusy;
	for(int i = 0; i < NbFoodSpawnedBeginPlay; i++)
	{
		ASpotFood * FirstSpawnFood = GetRandomSpotFood(ListSpotFoodAlreadyBusy);
		
		if(FirstSpawnFood != nullptr)
		{
			AFood * FirstFoodRandomized = SpawnFood(FirstSpawnFood->GetTransform());
			FirstSpawnFood->StoreFood(FirstFoodRandomized);
			ListSpotFoodAlreadyBusy.Add(FirstSpawnFood);
		}
	}
}

ASpotFood * AFoodManager::GetRandomSpotFood(TArray<ASpotFood*> ListSpotFoodToIgnore)
{
	TArray<ASpotFood *> ListSpotFoodToRandomize;
	for(ASpotFood * SpotFood : ListSpotFood)
	{
		if(ListSpotFoodToIgnore.Contains(SpotFood))
		{
			continue;
		}

		ListSpotFoodToRandomize.Add(SpotFood);
	}

	if(ListSpotFoodToRandomize.Num() <= 0)
	{
		return nullptr;
	}
	
	const int IndexSelectedSpotFood = FMath::RandRange(0, ListSpotFoodToRandomize.Num()-1);		

	return ListSpotFoodToRandomize[IndexSelectedSpotFood];
}

void AFoodManager::SpawnFoodSpot()
{
	if(BP_SpotFood != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		ASpotFood * SpotFoodCreated = GetWorld()->SpawnActor<ASpotFood>(BP_SpotFood, this->GetTransform(), SpawnParams);

		if(SpotFoodCreated==nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("NO Blueprint for SpotFood"));
			return;
		}
		
		ListSpotFood.Add(SpotFoodCreated);
		
		#if WITH_EDITOR
				SpotFoodCreated->SetFolderPath(GetFolderPath());
		#endif
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blueprint for SpotFood"));
		return;
	}	
}

void AFoodManager::RemoveFoodSpot(ASpotFood* SpotFood)
{
	if(SpotFood == nullptr)
	{
		return;
	}

	ListSpotFood.Remove(SpotFood);
	GetWorld()->RemoveActor(SpotFood->GetOwner(), true);
}

int AFoodManager::GetMaxFoodInScene() const
{
	return MaxFoodInScene;
}

bool AFoodManager::IsRemainingSlotFood() const
{
	return ListExistingFood.Num() < MaxFoodInScene;
}

int AFoodManager::GetCurrentNbFoodInScene() const
{
	return ListExistingFood.Num();
}

void AFoodManager::RemoveFoodInCounterFoodScene(AFood * FoodToIgnore)
{
	if(FoodToIgnore == nullptr)
	{
		return;
	}
	
	ListExistingFood.Remove(FoodToIgnore);	
}


void AFoodManager::DestroyFood(AFood * FoodToDestroy)
{
	if(FoodToDestroy == nullptr)
	{
		return;
	}

	if(ListExistingFood.Contains(FoodToDestroy))
	{
		ListExistingFood.Remove(FoodToDestroy);
	}
	FoodToDestroy->DestroyItem();
	//GetWorld()->RemoveActor(FoodToDestroy, true);
}


AFood * AFoodManager::SpawnFood()
{
	return SpawnFood(this->GetTransform());
}

AFood * AFoodManager::SpawnFood(FTransform SpawnTranform)
{
	if(BP_Food != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		AFood * FoodCreated = GetWorld()->SpawnActor<AFood>(BP_Food, GetTransform(), SpawnParams);
		FoodCreated->SetActorLocation(SpawnTranform.GetLocation());
		FoodCreated->SetActorRotation(SpawnTranform.GetRotation());

		if(FoodCreated==nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("NO Blueprint for Food"));
			return nullptr;
		}
		
		ListExistingFood.Add(FoodCreated);

		return FoodCreated;
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blueprint for Food"));
		return nullptr;
	}	
}


