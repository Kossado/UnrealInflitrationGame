// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Hero.generated.h"

UCLASS()
class GC_UE4CPP_API AHero : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Camera stick positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraStick;
	// Camera that follow the character
	UPROPERTY(VisibleAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
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

protected:
	// Called for forward/backward input
	void MoveForward(float Value);
	// Called for right/left input
	void MoveRight(float Value);
	// Called to setup the zoom's destination
	void ZoomIn();	
	void ZoomOut();
	// Called in Tick to zoom smoothly between the current zoom and the zoom's destination
	void SmoothZoom(float DeltaTime);
	// Menu Function
	void InvokeMenu();

};
