// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeObjectsComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFadeObjectsComponent::UFadeObjectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	// Add first collision type
	ObjectTypes.Add(ECC_WorldStatic);
}


// Called when the game starts
void UFadeObjectsComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	
	GetOwner()->GetWorld()->GetTimerManager().SetTimer(AddFadeObjectsTimer, this, &UFadeObjectsComponent::FadeObject, FadeInterval, true);
	GetOwner()->GetWorld()->GetTimerManager().SetTimer(ObjectComputeTimer, this, &UFadeObjectsComponent::UnFadeObject, FadeInterval, true);

	GetOwner()->GetWorld()->GetTimerManager().PauseTimer(ObjectComputeTimer);
	GetOwner()->GetWorld()->GetTimerManager().PauseTimer(AddFadeObjectsTimer);

	SetActivate(bIsActivate);
}


// Called every frame
void UFadeObjectsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFadeObjectsComponent::FadeObject()
{
	// Setting up Parameters for the trace
	const FVector TraceStart = UGameplayStatics::GetPlayerController(GetWorld(),0)->PlayerCameraManager->GetCameraLocation();
	const FVector TraceEnd = Character->GetActorLocation();
	FVector TraceLength = TraceStart - TraceEnd;
	const FQuat ActorQuat = Character->GetActorQuat();

	if (TraceLength.Size() < WorkDistance)
	{
		// Params for the trace collision
		FCollisionQueryParams TraceParams(TEXT("FadeObjectsTrace"), false, GetOwner());

		TraceParams.AddIgnoredActors(ActorsIgnore);
		TraceParams.bReturnPhysicalMaterial = false;

		TArray<FHitResult> HitArray;
		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

		// Convert ECollisionChannel to ObjectType
		for (int i = 0; i < ObjectTypes.Num(); ++i)
		{
			TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ObjectTypes[i].GetValue()));
		}
		// Check distance between camera and player for new object to fade, and add this in array
		GetOwner()->GetWorld()->SweepMultiByObjectType(HitArray, TraceStart, TraceEnd, ActorQuat, TraceObjectTypes,
				FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), TraceParams);

		for (int HitArrayIndex = 0; HitArrayIndex < HitArray.Num(); ++HitArrayIndex)
		{
			if (HitArray[HitArrayIndex].bBlockingHit && IsValid(HitArray[HitArrayIndex].GetComponent()) && !FadeObjectsHit.Contains(HitArray[HitArrayIndex].GetComponent()))
			{
				FadeObjectsHit.AddUnique(HitArray[HitArrayIndex].GetComponent());
			}
		}
	}

	// Add FadeObjects in a temporary Array
	for (int FadeObjIndex = 0; FadeObjIndex < FadeObjectsHit.Num(); ++FadeObjIndex)
	{
		// If not contains this component in fadeObjectsTemp
		if (!FadeObjectsTemp.Contains(FadeObjectsHit[FadeObjIndex]))
		{
			TArray<UMaterialInterface*> BaseMaterialsArray;
			TArray<UMaterialInstanceDynamic*> MidMaterialsArray;

			BaseMaterialsArray.Empty();
			MidMaterialsArray.Empty();

			FadeObjectsTemp.AddUnique(FadeObjectsHit[FadeObjIndex]);

			// For loop all materials ID in object
			for (int MatIndex = 0; MatIndex < FadeObjectsHit[FadeObjIndex]->GetNumMaterials(); ++MatIndex)
			{
				MidMaterialsArray.Add(UMaterialInstanceDynamic::Create(FadeMaterial, FadeObjectsHit[FadeObjIndex]));
				BaseMaterialsArray.Add(FadeObjectsHit[FadeObjIndex]->GetMaterial(MatIndex));

				// Set new material on object
				FadeObjectsHit[FadeObjIndex]->SetMaterial(MatIndex, MidMaterialsArray.Last());
			}
			// Create new fade object in array of objects to fade
			FFadeObjStruct NewObject;
			NewObject.NewFadingObject(FadeObjectsHit[FadeObjIndex], BaseMaterialsArray, MidMaterialsArray, FadeValue, true);
			// Add object to array
			FadeObjects.Add(NewObject);
		}
	}

	// Set hide to visible true if contains
	for (int FadeObjTmpIndex = 0; FadeObjTmpIndex < FadeObjectsTemp.Num(); ++FadeObjTmpIndex)
	{
		if (!FadeObjectsHit.Contains(FadeObjectsTemp[FadeObjTmpIndex]))
		{
			FadeObjects[FadeObjTmpIndex].SetHideOnly(false);
		}
	}

	// Clear array
	FadeObjectsHit.Empty();
}

void UFadeObjectsComponent::UnFadeObject()
{
	if (FadeObjects.Num() > 0)
	{
		// For loop all fade objects
		for (int i = 0; i < FadeObjects.Num(); ++i)
		{
			// For loop fadeMID array
			for (int t = 0; t < FadeObjects[i].FadeMID.Num(); ++t)
			{
				float TargetF;

				if (FadeObjects[i].bToHide)
				{
					TargetF = FadeValue;
				}
				else
				{
					TargetF = 1.0f;
				}

				FadeObjects[i].FadeMID[t]->SetScalarParameterValue("Fade", TargetF);

				CurrentFade = TargetF;

				FadeObjects[i].SetFadeAndHide(TargetF, FadeObjects[i].bToHide);
			}
			// remove index in array
			if (CurrentFade == 1.0f)
			{
				for (int BaseMatIndex = 0; BaseMatIndex < FadeObjects[i].BaseMatInterface.Num(); ++BaseMatIndex)
				{
					FadeObjects[i].PrimitiveComp->SetMaterial(BaseMatIndex, FadeObjects[i].BaseMatInterface[BaseMatIndex]);
				}
				
				FadeObjects.RemoveAt(i);
				FadeObjectsTemp.RemoveAt(i);
			}
		}
	}
}

void UFadeObjectsComponent::SetActivate(bool bActivate)
{
	bIsActivate = bActivate;

	if (!bIsActivate)
	{
		GetOwner()->GetWorld()->GetTimerManager().PauseTimer(ObjectComputeTimer);
		GetOwner()->GetWorld()->GetTimerManager().PauseTimer(AddFadeObjectsTimer);
	}
	else
	{
		GetOwner()->GetWorld()->GetTimerManager().UnPauseTimer(ObjectComputeTimer);
		GetOwner()->GetWorld()->GetTimerManager().UnPauseTimer(AddFadeObjectsTimer);
	}
}

void UFadeObjectsComponent::SetEnable(bool bEnable)
{
	bIsEnabled = bEnable;
}