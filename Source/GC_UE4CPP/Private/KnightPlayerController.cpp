// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPlayerController.h"

#include "Kismet/GameplayStatics.h"

AKnightPlayerController::AKnightPlayerController(): Super(),
                                                    BaseTurnRate(45.f),
                                                    BaseLookUpRate(45.f),
                                                    MinCameraDistance(100.f),
                                                    MaxCameraDistance(900.f),
                                                    CameraZoomSpeed(10.f),
                                                    CameraZoomSteps(45.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Define the Team ID of the Player - will be different from the AI
	TeamId = FGenericTeamId(0);
}

void AKnightPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainGameMode = Cast<AGCGameMode>(GetWorld()->GetAuthGameMode());

	if(MainGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AKnightPlayerController::BeginPlay - MainGameMode is null"));
		return;
	}
	
	PlayerCharacter = Cast<AKnightCharacter>(GetPawn());
	if(PlayerCharacter)
	{
		CamZoomDestination = PlayerCharacter->GetCameraSpringArm()->TargetArmLength;

		USkeletalMesh * ChoosenSkeletalMesh = MainGameMode->GetSkeletalMeshChoosenByPlayer();
		TSubclassOf<UAnimInstance> ChoosenAnimation = MainGameMode->GetAnimationChoosenByPlayer();
		
		if(ChoosenSkeletalMesh != nullptr /*&& ChoosenAnimation != nullptr*/)
		{
			PlayerCharacter->GetMesh()->SetSkeletalMesh(ChoosenSkeletalMesh);
			PlayerCharacter->GetMesh()->SetAnimClass(ChoosenAnimation);
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("AKnightPlayerController::BeginPlay - Skeletal or Animation are null"));
			return;
		}
	}
}

void AKnightPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SmoothZoom(DeltaSeconds);
}

void AKnightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setting up Key/Character Movements
	InputComponent->BindAxis("MoveForward",this, &AKnightPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight",this, &AKnightPlayerController::MoveRight);

	// Setting up Mouse/Camera Movements
	InputComponent->BindAxis("Turn", this, &AKnightPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &AKnightPlayerController::AddPitchInput);

	//Setting up Zoom In/Out
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AKnightPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AKnightPlayerController::ZoomOut);

	//Setting up Menu Inputs
	InputComponent->BindAction("InvokeMenu",IE_Pressed, this, &AKnightPlayerController::InvokeMenu);

	// Setting up interaction input
	InputComponent->BindAction("Interact", IE_Pressed, this, &AKnightPlayerController::Interact);
}

void AKnightPlayerController::MoveForward(float Value)
{
	if(MainGameMode != nullptr && !MainGameMode->IsRunning())
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

void AKnightPlayerController::MoveRight(float Value)
{
	if(MainGameMode != nullptr && !MainGameMode->IsRunning())
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

void AKnightPlayerController::ZoomIn()
{
	if(MainGameMode != nullptr && !MainGameMode->IsRunning())
	{
		return;
	}
	
	CamZoomDestination = FMath::Clamp(PlayerCharacter->GetCameraSpringArm()->TargetArmLength - CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void AKnightPlayerController::ZoomOut()
{
	if(MainGameMode != nullptr && !MainGameMode->IsRunning())
	{
		return;
	}
	
	CamZoomDestination = FMath::Clamp(PlayerCharacter->GetCameraSpringArm()->TargetArmLength + CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void AKnightPlayerController::SmoothZoom(float DeltaTime) const
{
	if(MainGameMode != nullptr && !MainGameMode->IsRunning())
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

void AKnightPlayerController::InvokeMenu()
{
	GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->LaunchMenuPause();
	}
}

void AKnightPlayerController::Interact()
{
	if(MainGameMode != nullptr && !MainGameMode->IsRunning())
	{
		return;
	}
	
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->Interact();
	}
}

FGenericTeamId AKnightPlayerController::GetGenericTeamId() const
{
	return TeamId;
}
