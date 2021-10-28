// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FadeObjectsComponent.h"
#include "GCCharacter.h"
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
	
	UFUNCTION()
	void Interact();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the player try to sit down
	virtual void SitDown(AChair* Chair) override;
	// Called when the player try to stand up
	virtual void StandUp() override;
	void StoreItem(AInteractiveItem* InteractiveChest);

private:
	// Camera stick positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;
	
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraPortraitStick;
	
	// Camera that follow the character
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* CameraPortraitComponent;
	// Base turn rate for the right/left camera movement in deg/sec
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;
	// Base Lookup rate for the up/down camera movement in deg/sec
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	// Minimum Length of the CameraStick
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float MinCameraDistance;
	// Maximum Length of the CameraStick
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float MaxCameraDistance;
	// Camera zoom speed
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomSpeed;
	// How much the camera will move with one mouse wheel input
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomSteps;
	// Destination of the camera for the smooth zoom Should be equal to CameraStick->TargetArmLength at the beggining
	float CamZoomDestination;

	// Component that allow to see through objects
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	UFadeObjectsComponent* FadeObjectsComponent;

	UPROPERTY(EditAnywhere)
	TArray<FName> NameSocketDetectionByAI;
	
public:
	// GETTERS / SETTERS
	FORCEINLINE USpringArmComponent* GetCameraSpringArm() const {return CameraSpringArm;}

	/*UPROPERTY(EditAnywhere, Category = Materials)
	UMaterial* BaseMaterial;*/
};