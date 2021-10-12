// Fill out your copyright notice in the Description page of Project Settings.


#include "IAEnnemyManager.h"

#include "IACharacter.h"
#include "IAEnnemyCharacterController.h"


// Sets default values
AIAEnnemyManager::AIAEnnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIAEnnemyManager::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle OutHandle;
	GLog->Log("launch timer");

	//Will call SpawnUsefulActor after the specified time
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AIAEnnemyManager::SpawnPawn, 2);
}

void AIAEnnemyManager::SpawnPawn()
{
	if(BP_CharacterIA)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// AIAEnnemyCharacterController* ActorControllerRef = GetWorld()->SpawnActor<AIAEnnemyCharacterController>(BP_ControllerIA, SpawnAIPatrolPoint->GetTransform(), SpawnParams);
		AIACharacter* ActorRef = GetWorld()->SpawnActor<AIACharacter>(BP_CharacterIA, SpawnAIPatrolPoint->GetTransform(), SpawnParams);
		// ActorControllerRef->Initialize(this, ActorRef, ListSpotFood, UnSpawnAIPatrolPoint);
		AController * ActorControllerRef =ActorRef->GetController(); 
		if(ActorControllerRef == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller is null"));
			return;
		}

		else if(!ActorControllerRef->IsA(AIAEnnemyCharacterController::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller isn't in a good type"));
			return;
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller is valid"));

			AIAEnnemyCharacterController * ControllerIA = dynamic_cast<AIAEnnemyCharacterController*>(ActorControllerRef);
			ControllerIA->Initialize(this, ListSpotFood, UnSpawnAIPatrolPoint, NbRetriesSpotBeforeBack);
		}
	}	
}

void AIAEnnemyManager::UnSpawnIA(AIAEnnemyCharacterController* UnSpawnIA)
{
	Super::UnSpawnIA(UnSpawnIA);
	GLog->Log("UnSpawned Ennemy " + UnSpawnIA->GetName());

}


// Called every frame
void AIAEnnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

