// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerTeam.h"

#include "GCGameMode.h"
#include "Kismet/GameplayStatics.h"

APlayerControllerTeam::APlayerControllerTeam(): Super(),
                                                BaseTurnRate(45.f),
                                                BaseLookUpRate(45.f),
                                                MinCameraDistance(100.f),
                                                MaxCameraDistance(900.f),
                                                CameraZoomSpeed(10.f),
                                                CameraZoomSteps(45.f)
{
	PrimaryActorTick.bCanEverTick = true;
	
	TeamId = FGenericTeamId(0);
}

void APlayerControllerTeam::BeginPlay()
{
	Super::BeginPlay();
	MainGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	PlayerCharacter = Cast<AGCPlayerCharacter>(GetPawn());
	if(PlayerCharacter)
	{
		CamZoomDestination = PlayerCharacter->GetCameraSpringArm()->TargetArmLength;
	}
}

void APlayerControllerTeam::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	SmoothZoom(DeltaSeconds);
}

void APlayerControllerTeam::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setting up Key/Character Movements
	InputComponent->BindAxis("MoveForward",this, &APlayerControllerTeam::MoveForward);
	InputComponent->BindAxis("MoveRight",this, &APlayerControllerTeam::MoveRight);

	// Setting up Mouse/Camera Movements
	InputComponent->BindAxis("Turn", this, &APlayerControllerTeam::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerControllerTeam::AddPitchInput);

	//Setting up Zoom In/Out
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerControllerTeam::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APlayerControllerTeam::ZoomOut);

	//Setting up Menu Inputs
	InputComponent->BindAction("InvokeMenu",IE_Pressed, this, &APlayerControllerTeam::InvokeMenu);

	// Setting up interaction input
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerControllerTeam::Interact);
}

void APlayerControllerTeam::MoveForward(float Value)
{
	if(MainGameMode->GetCurrentGameState() != EGS_PLAYING)
	{
		return;
	}
	
	if(PlayerCharacter && Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator YawRotation{0,GetControlRotation().Yaw,0};
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Based on the X axis (Forward/Backward)
		
		PlayerCharacter->AddMovementInput(Direction, Value);
	}
}

void APlayerControllerTeam::MoveRight(float Value)
{
	if(MainGameMode->GetCurrentGameState() != EGS_PLAYING)
	{
		return;
	}
	
	if(PlayerCharacter && Value != 0.0f)
	{
		// Find out which way is right
		const FRotator YawRotation{0,GetControlRotation().Yaw,0};
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Based on the Y Axis (Right/Left)
		
		PlayerCharacter->AddMovementInput(Direction, Value);
	}
}

void APlayerControllerTeam::ZoomIn()
{
	if(MainGameMode->GetCurrentGameState() != EGS_PLAYING)
	{
		return;
	}
	
	CamZoomDestination = FMath::Clamp(PlayerCharacter->GetCameraSpringArm()->TargetArmLength - CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void APlayerControllerTeam::ZoomOut()
{
	if(MainGameMode->GetCurrentGameState() != EGS_PLAYING)
	{
		return;
	}
	
	CamZoomDestination = FMath::Clamp(PlayerCharacter->GetCameraSpringArm()->TargetArmLength + CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void APlayerControllerTeam::SmoothZoom(float DeltaTime) const
{
	if(MainGameMode->GetCurrentGameState() != EGS_PLAYING)
	{
		return;
	}
	
	if(!FMath::IsNearlyEqual(PlayerCharacter->GetCameraSpringArm()->TargetArmLength, CamZoomDestination, 0.5f))
	{
		// Smooth zoom over time
		PlayerCharacter->GetCameraSpringArm()->TargetArmLength = FMath::FInterpTo(
			PlayerCharacter->GetCameraSpringArm()->TargetArmLength,//Current value
			CamZoomDestination,// Target Value
			DeltaTime,// Time passed
			CameraZoomSpeed//Speed
			);
	}
}

void APlayerControllerTeam::InvokeMenu()
{
	AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->LaunchMenuPause();
	}
}

void APlayerControllerTeam::Interact()
{
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->Interact();
	}
}

FGenericTeamId APlayerControllerTeam::GetGenericTeamId() const
{
	return TeamId;
}
