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
		AI_PerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
	}
}


bool AIAEnnemyCharacterController::Initialize(AIAEnnemyManager* IAEnnemyManagerSpawner, TArray<AIASpotFoodPoint *> ListSpotFoodsPoints, AIAPatrolPoint * SetUnSpawnPatrolPoint, unsigned int NbRetriesBeforeBackUnSpawn)
{
	if(!Super::Initialize(IAEnnemyManagerSpawner, TArray<AIAPatrolPoint*>(ListSpotFoodsPoints), SetUnSpawnPatrolPoint))
	{
		return false;
	}
	
	AI_PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AIAEnnemyCharacterController::SightPlayer);

	IAEnnemyManager = IAEnnemyManagerSpawner;
	this->NbRetriesBeforeBack = NbRetriesBeforeBackUnSpawn; 

	return true;
}

//We override the basic function because the parent function compare this IA controller with actor seen (here it's IA Character)
//So we go get the controller of this actor and thus compare the both controllers with have both an TeamID while IACharacter doesn't have one
//and return neutral team if we compare with IACharacter
ETeamAttitude::Type AIAEnnemyCharacterController::GetTeamAttitudeTowards(const AActor& Other) const
{

	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	return ETeamAttitude::Neutral;
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
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Blue, FString::Printf(TEXT("Detection of %s int team %d"), ToCStr(GetName()), GetGenericTeamId().GetId()));

	for(int i = 0; i < UpdateActors.Num();i++)
	{
		IGenericTeamAgentInterface* teamIA = dynamic_cast<IGenericTeamAgentInterface*>(UpdateActors[i]);
		GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Blue, FString::Printf(TEXT("See %s"), ToCStr(UpdateActors[i]->GetName())));
		
		if(teamIA)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Blue, FString::Printf(TEXT("on team %d"), teamIA->GetGenericTeamId().GetId()));	
		}
		
	}
	

	
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
