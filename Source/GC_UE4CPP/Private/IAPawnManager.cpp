
// Fill out your copyright notice in the Description page of Project Settings.


#include "IAPawnManager.h"

// Sets default values
AIAPawnManager::AIAPawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIAPawnManager::BeginPlay()
{
	Super::BeginPlay();
}

bool AIAPawnManager::UnSpawnIA(AActor* UnSpawnIA)
{
	GLog->Log("Pawn UnSpawned  " + UnSpawnIA->GetName());
	return UnSpawnIA->Destroy();
}


// Called every frame
void AIAPawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

