// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChasePlayer.h"

#include "AIController.h"
#include "Hero.h"
#include "IAEnnemyCharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"



EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Succeeded;
}
