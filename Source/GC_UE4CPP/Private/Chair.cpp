// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

// Sets default values
AChair::AChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up Scene Component
	/*SceneComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	RootComponent = SceneComponent;*/
	
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	RootComponent = StaticMesh;

	//Set up Location to sit Component
	SitLocationComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Sit Location")));
	SitLocationComponent->SetupAttachment(RootComponent);
	SetCollisionProperties(false);
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

void AChair::SetCollisionProperties(bool bUsed)
{
	if(bUsed)
	{
		StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
	}else
	{
		StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
	}
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

