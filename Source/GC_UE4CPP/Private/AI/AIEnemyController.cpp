// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIEnemyController.h"

#include "BlueprintEditor.h"
#include "ChaosInterfaceWrapperCore.h"
#include "Managers/GCGameMode.h"
#include "Food/SpotFood.h"
#include "AI/AIEnemyManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Engine/SkeletalMeshSocket.h"
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

	if(AICharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character for controller not found"));
		return false;
	}

	if(AICharacter->BehaviourTree->BlackboardAsset)
	{
		Blackboard->InitializeBlackboard(*(AICharacter)->BehaviourTree->BlackboardAsset);
		Blackboard->SetValueAsVector("LocationUnSpawn", AIEnemyManager->GetUnSpawnPoint()->GetActorLocation());
		Blackboard->SetValueAsBool("NeedNewSpot", true);
		Blackboard->SetValueAsObject("SelfActor", GetCharacter());
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
	if(!bCarryFood && FoodToCarry != nullptr)
	{
		bCarryFood = true;		
		AttributedFood = FoodToCarry;
		AICharacter->GrabItem(FoodToCarry);
		GetBlackboardComponent()->SetValueAsObject("Food", AttributedFood);
		GetBlackboardComponent()->SetValueAsBool("bCarryFood", true);
		GetBlackboardComponent()->SetValueAsBool("bHasToPutFood", true);
		GetBlackboardComponent()->SetValueAsBool("bHasDroppedFood", false);
		GetBlackboardComponent()->SetValueAsVector("LocationDroppedFood", FVector::ZeroVector);

	}
}

bool AAIEnemyController::PutFoodAtStand()
{
	if(CurrentSpotFoodTarget == nullptr)
	{
		return false;
	}
	
	AICharacter->StoreFood(CurrentSpotFoodTarget);
	GetBlackboardComponent()->SetValueAsBool("bCarryFood", false);
	GetBlackboardComponent()->SetValueAsBool("bHasToPutFood", false);
	GetBlackboardComponent()->SetValueAsObject("Food", nullptr);
	GetBlackboardComponent()->SetValueAsBool("bHasDroppedFood", false);
	GetBlackboardComponent()->SetValueAsVector("LocationDroppedFood", FVector::ZeroVector);
	return true;
}


void AAIEnemyController::DropFood()
{
	if(bCarryFood && AttributedFood != nullptr)
	{
		bCarryFood = false;
		AICharacter->DropItem();
		GetBlackboardComponent()->SetValueAsBool("bCarryFood", false);
		GetBlackboardComponent()->SetValueAsBool("bHasDroppedFood", true);
		GetBlackboardComponent()->SetValueAsVector("LocationDroppedFood", GetCharacter()->GetActorLocation());
	}
}

AAIEnemyManager* AAIEnemyController::GetAIEnemyManager() const
{
	return AIEnemyManager;
}


void AAIEnemyController::SightPlayer(AActor* UpdateActor, FAIStimulus FaiStimulus)
{
	bool HasSensedSomeone = FaiStimulus.WasSuccessfullySensed();

	if(!UpdateActor->IsA(AGCCharacter::StaticClass()))
	{
		return;
	}

	AGCCharacter * CharacterSeen = Cast<AGCCharacter>(UpdateActor);

	if(CharacterSeen == nullptr)
	{
		return;		
	}
	
	if(HasSensedSomeone)
	{
		//Change current target only if distance with the seen player is less than previous target or if he doesn't see the previous target
		//If it's the same target, we continue instruction to update positions
		if(TargetChased != CharacterSeen)
		{
			if(bCurrentlySeeTarget && TargetChased != nullptr && ((CharacterSeen->GetActorLocation() - GetCharacter()->GetActorLocation()).SizeSquared()) > (TargetChased->GetActorLocation() - GetCharacter()->GetActorLocation()).SizeSquared())
			{
				return;
			}
		}

		TargetChased = CharacterSeen;
		bCurrentlySeeTarget = true;
		Blackboard->SetValueAsBool("bHasSeenPlayer", true);
		Blackboard->SetValueAsBool("bHasLineOfSight", true);
		Blackboard->SetValueAsObject("TargetChase", CharacterSeen);

		if(CharacterSeen->GetSocketBaseCharacter() != nullptr)
		{
			Blackboard->SetValueAsVector("LastLocationSawPlayer", CharacterSeen->GetSocketBaseCharacterLocation());
			Blackboard->SetValueAsVector("LocationSearchPlayer", CharacterSeen->GetSocketBaseCharacterLocation());			
		}

		else
		{
			Blackboard->SetValueAsVector("LastLocationSawPlayer", CharacterSeen->GetActorLocation());
			Blackboard->SetValueAsVector("LocationSearchPlayer", CharacterSeen->GetActorLocation());
		}
	}
	else if(TargetChased == CharacterSeen)
	{
		Blackboard->SetValueAsBool("bHasLineOfSight", false);
		
		if(CharacterSeen->GetSocketBaseCharacter() != nullptr)
		{
			Blackboard->SetValueAsVector("DirectionTakenByTarget", CharacterSeen->GetActorForwardVector());
			Blackboard->SetValueAsVector("LastLocationSawPlayer", CharacterSeen->GetSocketBaseCharacterLocation());
		}

		else
		{
			Blackboard->SetValueAsVector("DirectionTakenByTarget", CharacterSeen->GetActorForwardVector());
			Blackboard->SetValueAsVector("LastLocationSawPlayer", CharacterSeen->GetActorLocation());
		}
		
		bCurrentlySeeTarget = false;

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

void AAIEnemyController::UnSpawn()
{
	AICharacter->UnSpawn();
}

void AAIEnemyController::Rotate(const FRotator NextRotation) const
{
	AICharacter->SetActorRotation(NextRotation);
}

void AAIEnemyController::HasHitPlayer() const
{
	AGCGameMode * GameMode = Cast<AGCGameMode>(GetWorld()->GetAuthGameMode());

	if(GameMode != nullptr)
	{
		GameMode->Defeat();
	}
}

void AAIEnemyController::ForgetTarget()
{	
	Blackboard->SetValueAsBool("bHasSeenPlayer", false);
	Blackboard->SetValueAsBool("bHasLineOfSight", false);	
	Blackboard->SetValueAsObject("TargetChase", nullptr);
	Blackboard->SetValueAsVector("DirectionTakenByTarget",FVector::ZeroVector);
	Blackboard->SetValueAsVector("LastLocationSawPlayer", FVector::ZeroVector);

	bCurrentlySeeTarget = false;
	TargetChased = nullptr;
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

void AAIEnemyController::UnSpawn()
{
	
	AIEnemyManager->UnSpawnAIAndPrepareRespawn(this);
}

