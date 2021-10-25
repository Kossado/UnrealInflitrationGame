// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/Food.h"

#include "DrawDebugHelpers.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFood::AFood() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	SetRootComponent(StaticMesh);
	//Set up food state
	SetFoodState(EFS_Dropped);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	if(IsOnGround())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on ground"), *GetName());
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s isn't on ground"), *GetName());
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

	if(FoodState != EFoodState::EFS_Dropped)
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

void AFood::SetFoodProperties(EFoodState State)
{
	switch (State)
	{
		case EFoodState::EFS_PickedUp:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(false);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EFoodState::EFS_Dropped:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(true);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			break;
		case EFoodState::EFS_Stored:
			StaticMesh->SetSimulatePhysics(false);
			StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		default:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(true);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			break;
	}
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::SetFoodState(EFoodState State)
{
	FoodState = State;
	SetFoodProperties(State);
}

