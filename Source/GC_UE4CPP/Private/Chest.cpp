// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

#include "GCGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Setup scene component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Food Parent")));
	RootComponent = SceneComponent;	
	// Setup Mesh Component
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Chest Mesh"));
	ChestMesh->SetupAttachment(RootComponent);
	ChestMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);	
	// Setup food position in chest
	FoodPlaceholder.Init(nullptr,5);
	for(int i = 0; i < FoodPlaceholder.Num();i++)
	{
		FString Name = TEXT("FoodPlaceholder");
		Name.Append(FString::FromInt(i));
		FoodPlaceholder[i] = CreateDefaultSubobject<USceneComponent>(FName(Name));
		FoodPlaceholder[i]->SetupAttachment(SceneComponent);
		FoodPlaceholder[i]->SetRelativeLocation(FVector(i*20,0.f,0.f));
	}
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

