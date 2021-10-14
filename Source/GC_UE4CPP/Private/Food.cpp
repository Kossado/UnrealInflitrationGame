// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Kismet/GameplayStatics.h"

#include "Hero.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	//Set up food state
	SetFoodState(EFS_Dropped);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
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
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			break;
		case EFoodState::EFS_Stored:
			StaticMesh->SetSimulatePhysics(true); // = false
			StaticMesh->SetCollisionResponseToAllChannels(ECR_Block); // = Ignore
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		default:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(true);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
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

