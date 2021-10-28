// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIEnemyManager.h"

#include "AI/AIEnemyCharacter.h"
#include "AI/AIEnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Managers/GCGameMode.h"

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

	MainGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MainGameMode != nullptr)
	{
		MainGameMode->EnemyManager = this;
	}
}

void AAIEnemyManager::Initialize()
{
	FTimerHandle OutHandle;
	AGCGameMode * GameMode = Cast<AGCGameMode>(GetWorld()->GetAuthGameMode());

	if(GameMode != nullptr)
	{
		if(GameMode->GetPlayerTeamId() == 0)
		{
			EnemyTeamId = 1;
		}

		else
		{
			EnemyTeamId = 0;
		}
	}

	SkeletalMeshesWithAnimation = GameMode->GetTeamSkeletalMeshes(EnemyTeamId);
	
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
	if(SpawnAIPatrolPoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAIEnemyManager::SpawnPawn - SpawnAIPatrolPoint is null"));
		return;
	}
	
	if(SkeletalMeshesWithAnimation.Num()>0)
	{
		int indexMesh = FMath::RandRange(0, SkeletalMeshesWithAnimation.Num()-1);
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AAIEnemyCharacter* ActorCharacterRef = GetWorld()->SpawnActor<AAIEnemyCharacter>(BP_CharacterAI, GetTransform(), SpawnParams);

		if(ActorCharacterRef == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AAIEnemyManager::SpawnPawn - ActorCharacterRef is null"));
			return;
		}
		
		ActorCharacterRef->SetActorLocation(SpawnAIPatrolPoint->GetActorLocation());
		ActorCharacterRef->SetActorRotation(SpawnAIPatrolPoint->GetActorRotation());

		if(SkeletalMeshesWithAnimation[indexMesh].SkeletalMeshKnight != nullptr && SkeletalMeshesWithAnimation[indexMesh].Anim!=nullptr)
		{
			ActorCharacterRef->GetMesh()->SetSkeletalMesh(SkeletalMeshesWithAnimation[indexMesh].SkeletalMeshKnight);
			ActorCharacterRef->GetMesh()->SetAnimClass(SkeletalMeshesWithAnimation[indexMesh].Anim);
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("AAIEnemyManager::SpawnPawn - SkeletalMeshKnight or Animation are null"));
			return;
		}
		
		// ActorControllerRef->Initialize(this, ActorRef, ListSpotFood, UnSpawnAIPatrolPoint);
		AController * ActorControllerRef =ActorCharacterRef->GetController(); 
		if(ActorControllerRef == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AAIEnemyManager::SpawnPawn - ActorControllerRef is null"));
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

	else
	{
		UE_LOG(LogTemp, Error, TEXT("AAIEnemyManager::SpawnPawn - No List of Skeletall Meshes"));
		return;
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

	UnSpawnAI->UnSpawn();
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

