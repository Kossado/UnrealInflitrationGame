// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood():
FoodState(EFoodState::EFS_Dropped)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	SetRootComponent(StaticMesh);
	//Set up AreaSphere
	AreaSphere = CreateDefaultSubobject<USphereComponent>(FName("AreaSphere"));
	AreaSphere->SetupAttachment(StaticMesh);

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	// Setup overlap for AreaSphere
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AFood::OnSphereBeginOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AFood::OnSphereEndOverlap);
	SetFoodProperties(EFoodState::EFS_Dropped);
	
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
			//Set AreaSphere properties
			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EFoodState::EFS_Dropped:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(true);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//Set AreaSphere properties
			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			break;
	}
}

void AFood::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Begin Overlap With AreaSphere"));
		
}

void AFood::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("End Overlap With AreaSphere"));
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

