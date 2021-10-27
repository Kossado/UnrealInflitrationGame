// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/SpotFood.h"

// Sets default values
ASpotFood::ASpotFood() : Super()
{

}

void ASpotFood::Initialize(AFoodManager * FoodManagerSpawner)
{
	FoodManager = FoodManagerSpawner;
}


// Called when the game starts or when spawned
void ASpotFood::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASpotFood::HasFood() const
{
	return StoredFood != nullptr;
}

bool ASpotFood::StoreFood(AFood * FoodToStore)
{
	if(HasFood())
	{
		return false;
	}
	
	FoodToStore->SetActorLocation(this->GetActorLocation());
	FoodToStore->SetActorRotation(this->GetActorRotation());
	StoredFood = FoodToStore;
	return true;
}

AFood * ASpotFood::TakeFood()
{
	if(StoredFood == nullptr)
	{
		return nullptr;
	}

	AFood * TokenFood = StoredFood;
	StoredFood = nullptr;
	return TokenFood;
}


bool ASpotFood::IsOnGround() const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;
	
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_AILineOfSight, true, this);

	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), GetActorLocation() - FVector::UpVector * 100
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
			, CollisionQueryParams);

	if(bHitSocket && HitResult.GetActor()->ActorHasTag("Ground"))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ %s ] is on ground"));

		return true;
	}

	else
	{
		if(bHitSocket)
		{
			UE_LOG(LogTemp, Warning, TEXT("support has name %s"), *HitResult.GetActor()->GetName());
		}
		return false;
	}
}

//Return bounds on object on what is landed
bool ASpotFood::GetBoundsSupportFood(FVector& Origin, FVector& BoxExtent)
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
	Origin = FVector::ZeroVector;
	BoxExtent = FVector::ZeroVector;

	
	FHitResult HitResult;
	
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_AILineOfSight, true, this);

	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), GetActorLocation() - FVector::UpVector * 100
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic))
			, CollisionQueryParams);

	
	if(bHitSocket)
	{
		HitResult.GetActor()->GetActorBounds(false, Origin, BoxExtent, true);
		return true;
	}

	else
	{
		return false;
	}
	
}

