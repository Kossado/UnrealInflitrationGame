// Fill out your copyright notice in the Description page of Project Settings.


#include "IAEnnemyManager.h"

#include "IACharacter.h"
#include "IAEnnemyCharacterController.h"
#include "Math/UnrealMathUtility.h"


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
	for(int i = 0; i < NbIAStartingGame; i++)
	{
		SpawnPawn();
	}


	if(TimeToPop3rdIA >= 0)
	{
		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AIAEnnemyManager::SpawnPawn, TimeToPop3rdIA);
	}
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

			if(ListIAControllerOnScene.Num() > 0 )
			{
				GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Red,  FString::Printf(TEXT("attitude %d"), ListIAControllerOnScene[0]->GetTeamAttitudeTowards(*ControllerIA)));
			}
			ListIAControllerOnScene.Add(ControllerIA);			
		}
	}	
}

void AIAEnnemyManager::UnSpawnIAAndPrepareRespawn(AIAEnnemyCharacterController* IAToDestroy)
{
	UnSpawnIA(IAToDestroy);

	if(ListIAControllerOnScene.Num() <= 0)
	{
		GLog->Log("spawn immediately");
		SpawnPawn();
	}

	else
	{
		GLog->Log("random time");
		SpawnIARandomTime(TimeMinBetweenRepopIA, TimeMaxBetweenRepopIA);
	}
}

void AIAEnnemyManager::UnSpawnIA(AIAEnnemyCharacterController* UnSpawnIA)
{
	if(ListIAControllerOnScene.Contains(UnSpawnIA))
	{
		ListIAControllerOnScene.Remove(UnSpawnIA);	
	}
	
	Super::UnSpawnIA(UnSpawnIA->GetCharacter());		
}

void AIAEnnemyManager::SpawnIARandomTime(int TimeMin, int TimeMax)
{
	TimeMin=(TimeMin< 0)?0:TimeMin;
	TimeMax=(TimeMax< 0)?5:TimeMax;
		
	int TimeSpawnNewIA = FMath::RandRange(TimeMin, TimeMax);

	if(TimeSpawnNewIA <= 0)
	{
		SpawnPawn();
	}

	else
	{
		FTimerHandle OutHandle;
		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AIAEnnemyManager::SpawnPawn, TimeSpawnNewIA);
	}
}

// Called every frame
void AIAEnnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

