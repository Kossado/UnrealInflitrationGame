// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"

#include "GenericTeamAgentInterface.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHero::AHero():
BaseTurnRate(45.f),
BaseLookUpRate(45.f),
MinCameraDistance(200.f),
MaxCameraDistance(600.f),
CameraZoomSpeed(10.f),
CameraZoomSteps(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera stick
	CameraStick = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Stick"));
	CameraStick->SetupAttachment(RootComponent);
	CameraStick->TargetArmLength = 300.f; // Distance between the camera and the character
	CameraStick->bUsePawnControlRotation = true; // Rotate based on the controller
	CameraStick->SetRelativeRotation(FRotator(0.f,-30.f,0.f));

	// Create Camera that will follow the character
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	CameraComponent->SetupAttachment(CameraStick, USpringArmComponent::SocketName); // Attach Camera to end on the stick
	CameraComponent->bUsePawnControlRotation = false; // Camera doesn't rotate relative to arm

	// Don't rotate when the controller rotates. The controller only affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character rotate in the direction of input ...
	GetCharacterMovement()->RotationRate = FRotator(0.f,540.f,0.f); // ... at this rate	
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
	CamZoomDestination = CameraStick->TargetArmLength;
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SmoothZoom(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Key/Character Movements
	PlayerInputComponent->BindAxis("MoveForward",this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &AHero::MoveRight);

	// Setting up Mouse/Camera Movements
	/*PlayerInputComponent->BindAxis("Turn", this, &AHero::TurnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AHero::LookUpRate);*/
	PlayerInputComponent->BindAxis("Turn", this, &AHero::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AHero::AddControllerPitchInput);

	//Setting up Zoom In/Out
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AHero::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AHero::ZoomOut);
}

void AHero::MoveForward(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is forward
		const FRotator YawRotation{0,Controller->GetControlRotation().Yaw,0};
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Based on the X axis (Forward/Backward)
		
		AddMovementInput(Direction, Value);
	}
}

void AHero::MoveRight(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator YawRotation{0,Controller->GetControlRotation().Yaw,0};
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Based on the Y Axis (Right/Left)
		
		AddMovementInput(Direction, Value);
	}
}

void AHero::ZoomIn()
{
	CamZoomDestination = FMath::Clamp(CameraStick->TargetArmLength - CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void AHero::ZoomOut()
{
	CamZoomDestination = FMath::Clamp(CameraStick->TargetArmLength + CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void AHero::SmoothZoom(float DeltaTime)
{
	if(!FMath::IsNearlyEqual(CameraStick->TargetArmLength, CamZoomDestination, 0.5f))
	{
		// Smooth zoom over time
		CameraStick->TargetArmLength = FMath::FInterpTo(
			CameraStick->TargetArmLength,//Current value
			CamZoomDestination,// Target Value
			DeltaTime,// Time passed
			CameraZoomSpeed//Speed
			);
	}
}

