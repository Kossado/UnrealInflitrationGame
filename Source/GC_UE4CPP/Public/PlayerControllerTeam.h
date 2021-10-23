// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCPlayerCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerTeam.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API APlayerControllerTeam : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APlayerControllerTeam();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;
	// Reference to the player character
	AGCPlayerCharacter* PlayerCharacter;
	// Called for forward/backward input
	void MoveForward(float Value);
	// Called for right/left input
	void MoveRight(float Value);
	// Called to setup the zoom's destination
	void ZoomIn();	
	void ZoomOut();
	// Called in Tick to zoom smoothly between the current zoom and the zoom's destination
	void SmoothZoom(float DeltaTime) const;
	// Launch menu Pause
	void InvokeMenu();
	UFUNCTION()
	void Interact();

private:
	// Base turn rate for the right/left camera movement in deg/sec
	UPROPERTY(EditAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;
	// Base Lookup rate for the up/down camera movement in deg/sec
	UPROPERTY(EditAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	// Minimum Length of the CameraSpringArm
	UPROPERTY(EditAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float MinCameraDistance;
	// Maximum Length of the CameraSpringArm
	UPROPERTY(EditAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float MaxCameraDistance;
	// Camera zoom speed
	UPROPERTY(EditAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomSpeed;
	// How much the camera will move with one mouse wheel input
	UPROPERTY(EditAnywhere, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomSteps;
	// Destination of the camera for the smooth zoom Should be equal to CameraSpringArm->TargetArmLength at the beggining
	float CamZoomDestination;
	
	// Useless ? Need to see with Benjamin's code
	FGenericTeamId TeamId;
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	
};
