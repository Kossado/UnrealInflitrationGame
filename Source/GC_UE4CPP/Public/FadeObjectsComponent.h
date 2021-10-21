// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FadeObjectsComponent.generated.h"

USTRUCT()
struct FFadeObjStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
	UPrimitiveComponent* PrimitiveComp;

	UPROPERTY()
	TArray<UMaterialInterface*> BaseMatInterface;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> FadeMID;

	UPROPERTY()
	float FadeCurrent;

	UPROPERTY()
	bool bToHide;

	void NewFadingObject(UPrimitiveComponent* NewComponent, TArray<UMaterialInterface*> NewBaseMat,
		TArray<UMaterialInstanceDynamic*> NewMID, float CurrentFade, bool bHide)
	{
		PrimitiveComp = NewComponent;
		BaseMatInterface = NewBaseMat;
		FadeMID = NewMID;
		FadeCurrent = CurrentFade;
		bToHide = bHide;
	}

	void SetHideOnly(bool bHide)
	{
		bToHide = bHide;
	}

	void SetFadeAndHide(float NewFade, bool bNewHide)
	{
		FadeCurrent = NewFade;
		bToHide = bNewHide;
	}

	//For Destroy
	void Destroy()
	{
		PrimitiveComp = nullptr;
	}

	//Constructor
	FFadeObjStruct()
	{
		PrimitiveComp = nullptr;
		FadeCurrent = 0;
		bToHide = true;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GC_UE4CPP_API UFadeObjectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFadeObjectsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void FadeObject();

	void UnFadeObject();

	// Enable or disable fade object worker
	UFUNCTION(BlueprintCallable, Category = "Fade Objects")
		void SetEnable(bool bEnable);

	// Pause or unpause fade object worker
	UFUNCTION(BlueprintCallable, Category = "Fade Objects")
		void SetActivate(bool bActivate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fade Objects")
		TArray<AActor*> ActorsIgnore;


private:

	TArray<FFadeObjStruct> FadeObjects;

	// Some worker timer
	FTimerHandle ObjectComputeTimer;
	FTimerHandle AddFadeObjectsTimer;

	// Temp variable
	float CurrentFade;
	
	// Primitive components temp variable
	UPROPERTY()
	TArray<UPrimitiveComponent*> FadeObjectsTemp;

	// Primitive components temp variable
	UPROPERTY()
	TArray<UPrimitiveComponent*> FadeObjectsHit;

	// Translucent material for fade object
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	UMaterialInstance* FadeMaterial;

	// Enable or disable fade object worker
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	bool bIsEnabled = true;

	// Pause or unpause fade object worker
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	bool bIsActivate = true;

	// Timer interval
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	float FadeInterval = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	float WorkDistance = 5000.0f;

	// Check trace block by this
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	TArray<TEnumAsByte<ECollisionChannel>> ObjectTypes;

	// Trace object size
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	float CapsuleHalfHeight = 88.0f;
	// Trace object size
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	float CapsuleRadius = 34.0f;
	
	UPROPERTY()
	ACharacter* Character;
	
	// Instance fade
	UPROPERTY(EditAnywhere, Category = "Fade Objects")
	float FadeValue = 0.25f;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
		
};
