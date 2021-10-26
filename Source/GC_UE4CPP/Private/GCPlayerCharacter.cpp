// Fill out your copyright notice in the Description page of Project Settings.


#include "GCPlayerCharacter.h"

#include "GenericTeamAgentInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GC_UE4CPP/HUD/GC_InGameInterface.h"

// Sets default values
AGCPlayerCharacter::AGCPlayerCharacter():
BaseTurnRate(45.f),
BaseLookUpRate(45.f),
MinCameraDistance(100.f),
MaxCameraDistance(900.f),
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

	// Create Camera that will follow the character
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	CameraComponent->SetupAttachment(CameraStick, USpringArmComponent::SocketName); // Attach Camera to end on the stick
	CameraComponent->bUsePawnControlRotation = false; // Camera doesn't rotate relative to arm

	// Create second camera stick
	CameraPortraitStick = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Portrait Stick"));
	CameraPortraitStick->SetupAttachment(RootComponent);
	CameraPortraitStick->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 35.0f), FRotator(0.0f, 180.0f, 0.0f));
	CameraPortraitStick->TargetArmLength = 80.f; // Distance between the camera and the character
	
	// Create Camera that will follow the portrait character
	CameraPortraitComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(FName("CameraPortrait"));
	CameraPortraitComponent->SetupAttachment(CameraPortraitStick, USpringArmComponent::SocketName); // Attach Camera to end on the stick
	CameraPortraitComponent->ShowOnlyActorComponents(this,false);

	/*UTextureRenderTarget2D* Hero3DPortrait = CameraPortraitComponent->TextureTarget;
	std::string ts = "TerrainMaterial";
	std::wstring ws(ts.begin(), ts.end());
	UMaterialInstance *terrainMaterialInstance = LoadObject<UMaterialInstance>(NULL, ws.c_str());
	UMaterialInstanceDynamic *dynamicTerrainMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, terrainMaterialInstance);
	dynamicTerrainMaterialInstance->SetTextureParameterValue("M_Hero3DPortrait", Hero3DPortrait); // This UTexture was created earlier and stored on the component*/
	
	// Don't rotate when the controller rotates. The controller only affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character rotate in the direction of input ...
	GetCharacterMovement()->RotationRate = FRotator(0.f,540.f,0.f); // ... at this rate

	// Setup fade objects component
	FadeObjectsComponent = CreateDefaultSubobject<UFadeObjectsComponent>(FName(TEXT("Fade Object Component")));
}

// Called when the game starts or when spawned
void AGCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CamZoomDestination = CameraStick->TargetArmLength;
}

// Called every frame
void AGCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SmoothZoom(DeltaTime);
	
	//SeeThroughComponent();
}

// Called to bind functionality to input
void AGCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Key/Character Movements
	PlayerInputComponent->BindAxis("MoveForward",this, &AGCPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &AGCPlayerCharacter::MoveRight);

	// Setting up Mouse/Camera Movements
	PlayerInputComponent->BindAxis("Turn", this, &AGCPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AGCPlayerCharacter::AddControllerPitchInput);

	//Setting up Zoom In/Out
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AGCPlayerCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AGCPlayerCharacter::ZoomOut);

	//Setting up Menu Inputs
	PlayerInputComponent->BindAction("InvokeMenu",IE_Pressed, this, &AGCPlayerCharacter::InvokeMenu);
}

void AGCPlayerCharacter::InvokeMenu()
{
	AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->LaunchMenuPause();
	}
}

void AGCPlayerCharacter::MoveForward(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is forward
		const FRotator YawRotation{0,Controller->GetControlRotation().Yaw,0};
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Based on the X axis (Forward/Backward)
		
		AddMovementInput(Direction, Value);
	}
}

void AGCPlayerCharacter::MoveRight(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator YawRotation{0,Controller->GetControlRotation().Yaw,0};
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Based on the Y Axis (Right/Left)
		
		AddMovementInput(Direction, Value);
	}
}

void AGCPlayerCharacter::ZoomIn()
{
	CamZoomDestination = FMath::Clamp(CameraStick->TargetArmLength - CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void AGCPlayerCharacter::ZoomOut()
{
	CamZoomDestination = FMath::Clamp(CameraStick->TargetArmLength + CameraZoomSteps, MinCameraDistance,MaxCameraDistance);
}

void AGCPlayerCharacter::SmoothZoom(float DeltaTime)
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

bool AGCPlayerCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;

	auto sockets = NameSocketDetectionByIA;
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor);
	CollisionQueryParams.AddIgnoredActor(this);
	
	for (int i = 0; i < sockets.Num(); i++)
	{		
		FVector SocketLocation = GetMesh()->GetSocketLocation(sockets[i]);

		const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, SocketLocation
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
			, CollisionQueryParams);

		NumberOfLoSChecksPerformed++;

		if (bHitSocket == false) {
			DrawDebugLine(GetWorld(), ObserverLocation, SocketLocation, FColor::Green, false, 1);
			
			OutSeenLocation = SocketLocation;
			OutSightStrength = 1;

			return true;
		}
	}

	const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation()
		, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic))
		, CollisionQueryParams);
	
	NumberOfLoSChecksPerformed++;
	
	if (bHit == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;
	
		return true;
	}

	OutSightStrength = 0;
	return false;
}

void AGCPlayerCharacter::SitDown()
{
	Super::SitDown();
	// Disable Mouse and Keyboard inputs
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(true);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(true);
	// Make the camera stay in front of the player
	CameraStick->bUsePawnControlRotation = false;
	CameraStick->SetRelativeRotation(FRotator(0.f,180.f,0.f));
}

void AGCPlayerCharacter::StandUp()
{
	Super::StandUp();
	// Enable Mouse and Keyboard inputs
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(false);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(false);
	// Allow the camera to move normally
	CameraStick->bUsePawnControlRotation = true;
}
