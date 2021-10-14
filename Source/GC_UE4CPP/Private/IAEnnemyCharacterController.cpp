// Fill out your copyright notice in the Description page of Project Settings.


#include "IAEnnemyCharacterController.h"
#include "IAEnnemyManager.h"
#include "IASpotFoodPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AIAEnnemyCharacterController::AIAEnnemyCharacterController(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	AI_PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AiPerceptionComponent");
	PerceptionComponent=AI_PerceptionComponent;
	UAISenseConfig_Sight * AI_ConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("AiConfigSight");
	SetGenericTeamId(FGenericTeamId(1));

	if(AI_PerceptionComponent)
	{
		AI_ConfigSight->SightRadius = 1000.0f;
		AI_ConfigSight->LoseSightRadius = 1000.0f;
		AI_ConfigSight->PeripheralVisionAngleDegrees = 135.f;
		AI_ConfigSight->DetectionByAffiliation.bDetectFriendlies=false;
		AI_ConfigSight->DetectionByAffiliation.bDetectNeutrals=false;
		AI_ConfigSight->DetectionByAffiliation.bDetectEnemies=true;
	
		AI_PerceptionComponent->ConfigureSense(*AI_ConfigSight);
		AI_PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
		AI_PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AIAEnnemyCharacterController::SightPlayer);
	}
}


bool AIAEnnemyCharacterController::Initialize(AIAEnnemyManager* IAEnnemyManagerSpawner, TArray<AIASpotFoodPoint *> ListSpotFoodsPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint, unsigned int NbRetriesBeforeBackUnSpawn)
{
	if(!Super::Initialize(IAEnnemyManagerSpawner, TArray<AIAPatrolPoint*>(ListSpotFoodsPoints), SetUnSpawnPatrolPoint))
	{
		return false;
	}

	

	IAEnnemyManager = IAEnnemyManagerSpawner;
	this->NbRetriesBeforeBack = NbRetriesBeforeBackUnSpawn; 
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Red,  FString::Printf(TEXT("TeamId %d"), GetGenericTeamId().GetId()));

	return true;
}

bool AIAEnnemyCharacterController::IsSpotHasFood(AIASpotFoodPoint * SpotFood)
{
	if(SpotFood == nullptr)
	{
		return false;
	}
	
	if(SpotFood->GetFoodState())
	{
		return true;
	}

	else
	{
		return false;
	}
}

AIAEnnemyManager* AIAEnnemyCharacterController::GetIAEnnemyManager() const
{
	return IAEnnemyManager;
}

void AIAEnnemyCharacterController::SightPlayer(const TArray<AActor*>& UpdateActors)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Red, "Player seen " +  GetGenericTeamId());

	
}

void AIAEnnemyCharacterController::SetNextTargetAIPatrolPoint(AIASpotFoodPoint * NextTargetAIPatrolPoint)
{
	Super::SetNextTargetAIPatrolPoint(NextTargetAIPatrolPoint);
	Blackboard->SetValueAsObject("SpotFood", NextTargetAIPatrolPoint);

	NbRetriesBeforeBack--;

	if(NbRetriesBeforeBack <= 0)
	{
		Blackboard->SetValueAsBool("GoUnSpawn", true);
	}
}
