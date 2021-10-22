// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBTT_LookAround.h"

#include "IAEnnemyCharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"

FTimerDelegate MyTestDel;

EBTNodeResult::Type UGCBTT_LookAround::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if(AIAEnnemyCharacterController * IAController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner()))
	{
		GCFBTLookAroundTaskMemory * MyMemory = CastInstanceNodeMemory<GCFBTLookAroundTaskMemory>(NodeMemory);

		MyMemory->CurrentTimeRotating=0;
		MyMemory->LeftSideAlreadyChecked=false;
		MyMemory->InitialRotation = IAController->GetCharacter()->GetActorRotation();
		
		bNotifyTick = 1;

		return EBTNodeResult::InProgress;
		
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get IAController from BehaviorTree"));
		return EBTNodeResult::Failed;
	}
}


void UGCBTT_LookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	GCFBTLookAroundTaskMemory* MyMemory = (GCFBTLookAroundTaskMemory*)NodeMemory;
	if (!OwnerComp.IsPaused())
	{
		AIAEnnemyCharacterController* MyController = Cast<AIAEnnemyCharacterController>(OwnerComp.GetAIOwner());
		if (MyController)
		{
			float AngleToAddFromInitialRotation = 0;
			
			if(LookTwoSidesSeparately)
			{
				if(MyMemory->LeftSideAlreadyChecked)
				{
					AngleToAddFromInitialRotation = FMath::Lerp(RangeLeft, RangeRight, MyMemory->CurrentTimeRotating/(SpeedRotation));
				}

				else
				{
					AngleToAddFromInitialRotation = FMath::Lerp(0.f, RangeLeft, MyMemory->CurrentTimeRotating/(SpeedRotation/2.f));
				}
			}

			else
			{
				AngleToAddFromInitialRotation = FMath::Lerp(0.f, Range, MyMemory->CurrentTimeRotating/SpeedRotation);
			}
			
			const FRotator NextRotation=MyMemory->InitialRotation + FRotator(0,AngleToAddFromInitialRotation, 0);
			MyController->GetCharacter()->SetActorRotation(NextRotation);

			if(LookTwoSidesSeparately)
			{
				if(MyMemory->LeftSideAlreadyChecked)
				{
					if(AngleToAddFromInitialRotation >= RangeRight)
					{
						MyMemory->RightSideAlreadyChecked = true;
						MyMemory->CurrentTimeRotating=0;
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
				}

				else
				{
					if(AngleToAddFromInitialRotation <= RangeLeft)
					{
						MyMemory->CurrentTimeRotating=0;
						MyMemory->LeftSideAlreadyChecked = true;
					}
				}
			}

			else if(AngleToAddFromInitialRotation >= Range)
			{
				MyMemory->CurrentTimeRotating=0;
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}

			MyMemory->CurrentTimeRotating += DeltaSeconds;
		}
		
	}
}

uint16 UGCBTT_LookAround::GetInstanceMemorySize() const
{
	return sizeof(GCFBTLookAroundTaskMemory);
}
