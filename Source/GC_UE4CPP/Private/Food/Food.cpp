// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/Food.h"

#include "DrawDebugHelpers.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFood::AFood():Super()
{
	SetItemProperties(EIS_Movable);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	if(IsOnGround())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on ground"), *(GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s isn't on ground"), *(GetName()));
		FVector Origin = FVector::ZeroVector;
		FVector BoxExtent = FVector::ZeroVector;
		if(GetBoundsSupportFood(Origin, BoxExtent))
		{
			UE_LOG(LogTemp, Warning, TEXT("Center [ %s ] Dimension [ %s ]"), *(Origin.ToString()), *(BoxExtent.ToString()));
		}
	}
}

bool AFood::IsOnGround() const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;
	
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_AILineOfSight, true, this);

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() - FVector::UpVector * 100, FColor::Red, true);
	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), GetActorLocation() - FVector::UpVector * 100
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
			, CollisionQueryParams);

	if(bHitSocket && HitResult.GetActor()->ActorHasTag("Ground"))
	{
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
bool AFood::GetBoundsSupportFood(FVector& Origin, FVector& BoxExtent)
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
	Origin = FVector::ZeroVector;
	BoxExtent = FVector::ZeroVector;

	if(GetCurrentItemState() != EItemState::EIS_Movable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Food isn't dropped"));

		return false;
	}
	
	FHitResult HitResult;
	
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_AILineOfSight, true, this);

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() - FVector::UpVector * 100, FColor::Red, true);
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
