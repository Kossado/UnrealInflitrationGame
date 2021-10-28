// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIEnemyManager.h"

#include "AI/AIEnemyCharacter.h"
#include "AI/AIEnemyController.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AAIEnemyManager::AAIEnemyManager() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle OutHandle;
	GLog->Log("launch timer");

	//Will call SpawnUsefulActor after the specified time
	for(int i = 0; i < NbAIStartingGame; i++)
	{
		SpawnPawn();
	}


	if(TimeToPop3rdAI >= 0)
	{
		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AAIEnemyManager::SpawnPawn, TimeToPop3rdAI);
	}
}

AFoodManager * AAIEnemyManager::GetFoodManager() const
{
	return FoodManager;
}

void AAIEnemyManager::SpawnPawn()
{
	if(List_BP_CharacterAI.Num()>0)
	{
		int indexBP = FMath::RandRange(0, List_BP_CharacterAI.Num()-1);

		if(List_BP_CharacterAI[indexBP] != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AAIEnemyCharacter* ActorCharacterRef = GetWorld()->SpawnActor<AAIEnemyCharacter>(List_BP_CharacterAI[indexBP], SpawnAIPatrolPoint->GetTransform(), SpawnParams);
			// ActorControllerRef->Initialize(this, ActorRef, ListSpotFood, UnSpawnAIPatrolPoint);
			AController * ActorControllerRef =ActorCharacterRef->GetController(); 
			if(ActorControllerRef == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Controller is null"));
				return;
			}

			else if(!ActorControllerRef->IsA(AAIEnemyController::StaticClass()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Controller isn't in a good type"));
				return;
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Controller is valid"));

				AAIEnemyController * ControllerAI = dynamic_cast<AAIEnemyController*>(ActorControllerRef);
				ControllerAI->Initialize(this, NbRetriesSpotBeforeBack);

				if(ListAIControllerOnScene.Num() > 0 )
				{
					GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Red,  FString::Printf(TEXT("attitude %d"), ListAIControllerOnScene[0]->GetTeamAttitudeTowards(*ControllerAI)));
				}
				ListAIControllerOnScene.Add(ControllerAI);

				if(FoodManager->IsRemainingSlotFood())
				{
					AFood * NewFood = FoodManager->SpawnFood();

					if(NewFood == nullptr)
					{
						UE_LOG(LogTemp, Error, TEXT("Fail to spawn food"));
						return;
					}

					ControllerAI->CarryFood(NewFood);
				}			
			}
		}
	}	
}


void AAIEnemyManager::UnSpawnAIAndPrepareRespawn(AAIEnemyController* AIToDestroy)
{
	UnSpawnAI(AIToDestroy);

	if(ListAIControllerOnScene.Num() <= 0)
	{
		GLog->Log("spawn immediately");
		SpawnPawn();
	}

	else
	{
		GLog->Log("random time");
		SpawnAIRandomTime(TimeMinBetweenRepopAI, TimeMaxBetweenRepopAI);
	}
}

void AAIEnemyManager::UnSpawnAI(AAIEnemyController* UnSpawnAI)
{
	if(UnSpawnAI==nullptr)
	{
		return;
	}
	
	if(ListAIControllerOnScene.Contains(UnSpawnAI))
	{
		ListAIControllerOnScene.Remove(UnSpawnAI);	
	}

	GetWorld()->DestroyActor(UnSpawnAI->GetCharacter());
}

void AAIEnemyManager::SpawnAIRandomTime(int TimeMin, int TimeMax)
{
	TimeMin=(TimeMin< 0)?0:TimeMin;
	TimeMax=(TimeMax< 0)?5:TimeMax;
		
	int TimeSpawnNewAI = FMath::RandRange(TimeMin, TimeMax);

	if(TimeSpawnNewAI <= 0)
	{
		SpawnPawn();
	}

	else
	{
		FTimerHandle OutHandle;
		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &AAIEnemyManager::SpawnPawn, TimeSpawnNewAI);
	}
}

// Called every frame
void AAIEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

