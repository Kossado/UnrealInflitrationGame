// Fill out your copyright notice in the Description page of Project Settings.


#include "MyIAController.h"

#include "AIPatrolPoint.h"
#include "StaticMeshAttributes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

AMyIAController::AMyIAController (const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTree");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyIAController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIACharacter * AICharacter = Cast<AIACharacter>(InPawn);

	if(AICharacter)
	{
		if(AICharacter->BehaviourTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(AICharacter)->BehaviourTree->BlackboardAsset);
		}
	}

	SetGenericTeamId(FGenericTeamId(1));
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "On possess");
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "name " + InPawn->GetHumanReadableName());	
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "key " + BlackboardComponent->GetKeyName(0).ToString());

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT("Size patrol %d"), PatrolPoints.Num()));

	
	BehaviorComponent->StartTree(*AICharacter->BehaviourTree);

}

void AMyIAController::OnUnPossess()
{
	Super::OnUnPossess();
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "On UnPossess");
}

void AMyIAController::SetNextTargetAIPatrolPoint(AActor * NextTargetAIPatrolPoint)
{
	if(PatrolPoints.Contains(NextTargetAIPatrolPoint))
	{
		CurrentPatrolPoints = PatrolPoints.Find(NextTargetAIPatrolPoint);
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, *(FString::Printf(TEXT("Current patrol point %d"), CurrentPatrolPoints)));

		BlackboardComponent->SetValueAsVector("PatrolLocation", NextTargetAIPatrolPoint->GetActorLocation());
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Try to set an invalid patrol point") );
	}
}

AActor * AMyIAController::GetRandomAIPatrolPoint(bool ExcludeCurrentPosition)
{
	int IndexNextPosition;
	//Si on souhaite une position random autre que celle déjà occupée par l'IA. Il faut également que l'IA est déjà une
	//position de départ pour pouvoir l'exclure
	if(ExcludeCurrentPosition && CurrentPatrolPoints>=0)
	{
		//On veut compris entre 0 et count-1, mais avec count = count - 1(position occupée à exclure)
		IndexNextPosition = FMath::RandRange(0, GetPatrolPoints().Num()-2);
		//Si le nombre obtenu est supérieur ou égal à l'index de la position courante, alors on l'incrémente car l'index
		//des positions supérieures est faussé par le fait qu'on est random sur "count-2" et non sur "count-1" 
		if(IndexNextPosition >= CurrentPatrolPoints)
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

