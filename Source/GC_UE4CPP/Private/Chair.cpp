// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

// Sets default values
AChair::AChair() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up Scene Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	RootComponent = SceneComponent;
	
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	StaticMesh->SetupAttachment(RootComponent);

	//Set up Location to sit Component
	SitLocationComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Sit Location")));
	SitLocationComponent->SetupAttachment(RootComponent);
	SitLocationComponent->SetRelativeRotation(FRotator(0.f,90.f,0.f));

}

FVector AChair::GetSitLocation()
{
	return SitLocationComponent->GetComponentLocation();
}

FRotator AChair::GetSitRotation()
{
	//return StaticMesh->GetComponentRotation();
	UE_LOG(LogTemp, Warning, TEXT("Try to sit on %s"), *(SitLocationComponent->GetName()));
	FRotator ret =  SitLocationComponent->GetComponentRotation();
	UE_LOG(LogTemp, Warning, TEXT("Try to sit %s"), *(ret.ToString()));
	UE_LOG(LogTemp, Verbose, TEXT("Success to sat on %s"), *(SitLocationComponent->GetName()));
	return ret;		
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

