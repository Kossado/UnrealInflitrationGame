// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIEnemyController.h"

#include "ChaosInterfaceWrapperCore.h"
#include "Food/SpotFood.h"
#include "AI/AIEnemyManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AAIEnemyController::AAIEnemyController(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTree");

	bStartAILogicOnPossess=true;
	bStopAILogicOnUnposses=true;

	AI_PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AiPerceptionComponent");
	PerceptionComponent=AI_PerceptionComponent;
	UAISenseConfig_Sight * AI_ConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("AiConfigSight");

	SetGenericTeamId(FGenericTeamId(1));

	if(AI_PerceptionComponent)
	{
		AI_ConfigSight->SightRadius = 1000.0f;
		AI_ConfigSight->LoseSightRadius = 1000.0f;
		AI_ConfigSight->PeripheralVisionAngleDegrees = 67.5f;
		AI_ConfigSight->DetectionByAffiliation.bDetectFriendlies=false;
		AI_ConfigSight->DetectionByAffiliation.bDetectNeutrals=false;
		AI_ConfigSight->DetectionByAffiliation.bDetectEnemies=true;
	
		AI_PerceptionComponent->ConfigureSense(*AI_ConfigSight);
		AI_PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
		AI_PerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
	}
}


// Called when the game starts or when spawned
void AAIEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AAIEnemyController::Initialize(AAIEnemyManager* AIEnemyManagerSpawner, unsigned int NbRetriesBeforeBackUnSpawn)
{
	AI_PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIEnemyController::SightPlayer);

	AICharacter = Cast<AAIEnemyCharacter>(GetCharacter());
	AIEnemyManager = AIEnemyManagerSpawner;
	this->NbRetriesBeforeBack = NbRetriesBeforeBackUnSpawn; 
	Blackboard->SetValueAsBool("NeedNewSpot", true);
	Blackboard->SetValueAsObject("SelfActor", GetCharacter());

	if(AICharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character for controller not found"));
		return false;
	}

	if(AICharacter->BehaviourTree->BlackboardAsset)
	{
		Blackboard->InitializeBlackboard(*(AICharacter)->BehaviourTree->BlackboardAsset);
		Blackboard->SetValueAsVector("LocationUnSpawn", AIEnemyManager->GetUnSpawnPoint()->GetActorLocation());
	}
		
	BehaviorComponent->StartTree(*AICharacter->BehaviourTree);
	

	return true;
}

//We override the basic function because the parent function compare this IA controller with actor seen (here it's IA Character)
//So we go get the controller of this actor and thus compare the both controllers with have both an TeamID while IACharacter doesn't have one
//and return neutral team if we compare with IACharacter
ETeamAttitude::Type AAIEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{

	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	return ETeamAttitude::Neutral;
}

bool AAIEnemyController::IsCarryingFood() const
{
	return AICharacter->HasItem();
}

void AAIEnemyController::CarryFood(AFood * FoodToCarry)
{
	if(FoodToCarry != nullptr)
	{
		AICharacter->GrabItem(FoodToCarry);
	}
}

bool AAIEnemyController::PutFoodAtStand()
{
	if(CurrentSpotFoodTarget == nullptr)
	{
		return false;
	}
	
	AICharacter->StoreFood(CurrentSpotFoodTarget);
	return true;
}


void AAIEnemyController::DropFood()
{
	AICharacter->DropItem();
}

AAIEnemyManager* AAIEnemyController::GetAIEnemyManager() const
{
	return AIEnemyManager;
}

///Mise à jour du sens de vue concernant un acteur de la scène
///On vérifie si il s'agit d'une vue sur un nouveau joueur ou si c'est une perte de vision
///
///Si on voit un nouveau joueur, on vérifie qu'on en poursuit pas déjà un
///Si on en poursuit un, on va sélectionner la cible la plus proche de l'IA et elle va devenir la nouvelle proie
///Si on a perdu la vision sur l'ancienne cible, alors on switch directement
///
///Si c'est une perte de vision sur la cible en cours, alors on va à sa dernière position connue, puis on cours dans la
///direction qu'avait prise le joueur
void AAIEnemyController::SightPlayer(AActor* UpdateActor, FAIStimulus FaiStimulus)
{
	bool HasSensedSomeone = FaiStimulus.WasSuccessfullySensed();

	if(HasSensedSomeone)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green, FString::Printf(TEXT("Detection of %s"), ToCStr(UpdateActor->GetName())));
		Blackboard->SetValueAsBool("HaveSeenPlayer", true);
		Blackboard->SetValueAsBool("HasLineOfSight", true);
		Blackboard->SetValueAsObject("TargetChase", UpdateActor);
		Blackboard->SetValueAsVector("LastLocationSawPlayer", UpdateActor->GetActorLocation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green, FString::Printf(TEXT("Lost of %s"), ToCStr(UpdateActor->GetName())));
		Blackboard->SetValueAsBool("HasLineOfSight", false);
		Blackboard->SetValueAsObject("TargetChase", nullptr);
		const FVector PreviousLocationTarget = Blackboard->GetValueAsVector("LastLocationSawPlayer");

		Blackboard->SetValueAsVector("DirectionTakenByTarget", UpdateActor->GetActorLocation() + (UpdateActor->GetActorLocation() - PreviousLocationTarget) * 500000);

		Blackboard->SetValueAsVector("LastLocationSawPlayer", UpdateActor->GetActorLocation());

	}
}

void AAIEnemyController::BeginRotation() const
{
	AICharacter->BeginRotate();
}

void AAIEnemyController::EndRotation() const
{
	AICharacter->EndRotate();
}

void AAIEnemyController::Rotate(const FRotator NextRotation) const
{
	AICharacter->SetActorRotation(NextRotation);
}

void AAIEnemyController::ForgetTarget()
{	
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green, FString::Printf(TEXT("Forget target")));
	Blackboard->SetValueAsBool("HaveSeenPlayer", false);
	Blackboard->SetValueAsBool("HasLineOfSight", false);	
	Blackboard->SetValueAsObject("TargetChase", nullptr);	
}

void AAIEnemyController::SetNextTargetSpotFood(ASpotFood * NextSpotFoodTarget)
{
	if(NextSpotFoodTarget == nullptr)
	{
		return;
	}
	
	ListSpotFoodAlreadyChecked.Add(CurrentSpotFoodTarget);
	CurrentSpotFoodTarget = NextSpotFoodTarget;
	Blackboard->SetValueAsObject("SpotFood", CurrentSpotFoodTarget);
}

void AAIEnemyController::WillNeedNewDestination()
{
	NbRetriesBeforeBack--;

	if(NbRetriesBeforeBack <= 0)
	{
		Blackboard->SetValueAsBool("GoUnSpawn", true);
	}
}
