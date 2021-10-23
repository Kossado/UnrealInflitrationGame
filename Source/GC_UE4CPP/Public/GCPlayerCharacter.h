// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FadeObjectsComponent.h"
#include "GCCharacter.h"
#include "Interactable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AISightTargetInterface.h"

#include "GCPlayerCharacter.generated.h"

UCLASS() 
class GC_UE4CPP_API AGCPlayerCharacter : public AGCCharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGCPlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor = nullptr, const bool* bWasVisible = nullptr, int32* UserData = nullptr) const override;

	// Grab an item
	void GrabItem(TSubclassOf<AActor> ItemClass);
	
	void OnEnterActor(AActor* InteractiveActor);
	void OnLeaveActor();
	UFUNCTION()
	void Action();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the player try to sit down
	virtual void SitDown() override;
	// Called when the player try to stand up
	virtual void StandUp() override;
	bool bHasItem = false;

	AActor* CurrentInteractiveActor;
	IInteractable* CurrentInteractive;
	
private:
	// Camera stick positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;
	// Camera that follow the character
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	// Component that allow to see through objects
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	UFadeObjectsComponent* FadeObjectsComponent;

	UPROPERTY(EditAnywhere)
	TArray<FName> NameSocketDetectionByIA;

	
public:
	// GETTERS / SETTERS
	FORCEINLINE USpringArmComponent* GetCameraSpringArm() const {return CameraSpringArm;}
	FORCEINLINE bool HasItem() const { return bHasItem; }
};