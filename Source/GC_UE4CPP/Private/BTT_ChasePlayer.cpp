// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChasePlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const Owner = OwnerComp.GetAIOwner();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	return EBTNodeResult::Succeeded;
}
