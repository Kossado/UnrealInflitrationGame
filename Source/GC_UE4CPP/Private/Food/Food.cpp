// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/Food.h"

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
}

bool AFood::IsOnGround() const
{
	static const FName NAME_IsOnGroundLine = FName(TEXT("NAME_IsOnGroundLine"));

	FHitResult HitResult;
	
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_IsOnGroundLine, true, this);

	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), GetActorLocation() - FVector::UpVector * 100
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
			, CollisionQueryParams);

	if(bHitSocket && HitResult.GetActor()->ActorHasTag("Ground"))
	{
		return true;
	}

	else
	{
		return false;
	}
}

//Return bounds on object on what is landed
bool AFood::GetBoundsSupportFood(FVector& Origin, FVector& BoxExtent)
{
	static const FName NAME_IsOnSupportLine = FName(TEXT("NAME_IsOnSupportLine"));
	Origin = FVector::ZeroVector;
	BoxExtent = FVector::ZeroVector;

	if(GetCurrentItemState() != EItemState::EIS_Movable)
	{
		return false;
	}
	
	FHitResult HitResult;
	
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_IsOnSupportLine, true, this);

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
