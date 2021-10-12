// Fill out your copyright notice in the Description page of Project Settings.


#include "IAPawnController.h"

#include "IAEnnemyManager.h"
#include "IAPatrolPoint.h"
#include "StaticMeshAttributes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

AIAPawnController::AIAPawnController (const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTree");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AIAPawnController::Initialize(AIAPawnManager* IAPawnerManagerSpawner, APawn* InPawn, const TArray<AIAPatrolPoint *> ListPatrolPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint)
{
	if(InPawn == nullptr ||IAPawnerManagerSpawner == nullptr)
	{
		return false;
	}

	IAPawnerManager = IAPawnerManagerSpawner;
	PatrolPoints = ListPatrolPoints;
	UnSpawnPatrolPoint = SetUnSpawnPatrolPoint;

	Possess(InPawn);
	
	return true;
}

void AIAPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	IAPawnerManager->UnSpawnIA(this);
	AIACharacter * AICharacter = Cast<AIACharacter>(InPawn);

	if(AICharacter)
	{
		if(AICharacter->BehaviourTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(AICharacter)->BehaviourTree->BlackboardAsset);
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT("Size patrol %d"), PatrolPoints.Num()));

	
	BehaviorComponent->StartTree(*AICharacter->BehaviourTree);

}

void AIAPawnController::OnUnPossess()
{
	Super::OnUnPossess();
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "On UnPossess");
}

AIAPatrolPoint * AIAPawnController::GetNextAIPatrolPoint()
{
	if(PatrolPoints.Num() <= 0)
	{
		return nullptr;
	}
	
	int indexNextAIPatrolPoints = 0;
	if(CurrentTargetPatrolPoints < 0)
	{
		indexNextAIPatrolPoints = 0;
	}

	else
	{
		indexNextAIPatrolPoints = CurrentTargetPatrolPoints+1;
	}

	if(indexNextAIPatrolPoints >= PatrolPoints.Num())
	{
		indexNextAIPatrolPoints = 0;
	}

	return PatrolPoints[indexNextAIPatrolPoints];
}


void AIAPawnController::SetNextTargetAIPatrolPoint(AIAPatrolPoint * NextTargetAIPatrolPoint)
{
	if(PatrolPoints.Contains(NextTargetAIPatrolPoint))
	{
		CurrentTargetPatrolPoints = PatrolPoints.Find(NextTargetAIPatrolPoint);
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, *(FString::Printf(TEXT("Current patrol point %d"), CurrentTargetPatrolPoints)));

		BlackboardComponent->SetValueAsVector("PatrolLocation", NextTargetAIPatrolPoint->GetActorLocation());
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Try to set an invalid patrol point") );
	}
}

AIAPatrolPoint * AIAPawnController::GetRandomAIPatrolPoint(bool ExcludeCurrentPosition)
{
	if(PatrolPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("List patrol point is empty") );
		return nullptr;
	}
	
	int IndexNextPosition;
	//Si on souhaite une position random autre que celle déjà occupée par l'IA. Il faut également que l'IA est déjà une
	//position de départ pour pouvoir l'exclure
	if(ExcludeCurrentPosition && CurrentTargetPatrolPoints>=0)
	{
		//On veut compris entre 0 et count-1, mais avec count = count - 1(position occupée à exclure)
		IndexNextPosition = FMath::RandRange(0, GetPatrolPoints().Num()-2);
		//Si le nombre obtenu est supérieur ou égal à l'index de la position courante, alors on l'incrémente car l'index
		//des positions supérieures est faussé par le fait qu'on est random sur "count-2" et non sur "count-1" 
		if(IndexNextPosition >= CurrentTargetPatrolPoints)
		{
			IndexNextPosition++;
		}		
	}

	else
	{
		IndexNextPosition = FMath::RandRange(0, GetPatrolPoints().Num()-1);		
	}

	if(IndexNextPosition >= GetPatrolPoints().Num())
	{
		IndexNextPosition = GetPatrolPoints().Num();
	}
	
	return  PatrolPoints[IndexNextPosition];
}

AIAPatrolPoint * AIAPawnController::GetUnSpawnPatrolPoint() const
{
	return UnSpawnPatrolPoint;
}

