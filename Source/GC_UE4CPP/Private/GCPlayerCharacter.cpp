#include "GCPlayerCharacter.h"

#include "Food/Food.h"
#include "Chair.h"
#include "GCGameMode.h"
#include "GenericTeamAgentInterface.h"
#include "GC_UE4CPP/HUD/GC_InGameInterface.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/InGameInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AGCPlayerCharacter::AGCPlayerCharacter() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera stick
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Stick"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 300.f; // Distance between the camera and the character
	CameraSpringArm->bUsePawnControlRotation = true; // Rotate based on the controller

	// Create Camera that will follow the character
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	CameraComponent->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName); // Attach Camera to end on the stick
	CameraComponent->bUsePawnControlRotation = false; // Camera doesn't rotate relative to arm

	// Create second camera stick
	CameraPortraitStick = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Portrait Stick"));
	CameraPortraitStick->SetupAttachment(RootComponent);
	CameraPortraitStick->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 35.0f), FRotator(0.0f, 180.0f, 0.0f));
	CameraPortraitStick->TargetArmLength = 80.f; // Distance between the camera and the character
	CameraPortraitStick->bDoCollisionTest = false; // Disable collision camera
	
	// Create Camera that will follow the portrait character
	CameraPortraitComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(FName("CameraPortrait"));
	CameraPortraitComponent->SetupAttachment(CameraPortraitStick, USpringArmComponent::SocketName); // Attach Camera to end on the stick
	CameraPortraitComponent->ShowOnlyActorComponents(this,false);
	CameraPortraitComponent->FOVAngle = 75.f; // Update value of angle camera
	CameraPortraitComponent->CaptureSource = ESceneCaptureSource::SCS_BaseColor; // Type of capture
	
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
}

// Called every frame
void AGCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AGCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AGCPlayerCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;

	auto sockets = NameSocketDetectionByAI;
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

void AGCPlayerCharacter::SitDown(AChair* Chair)
{
	Super::SitDown(Chair);
	// Disable Mouse and Keyboard inputs
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(true);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(true);
	// Make the camera stay in front of the player
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->SetRelativeRotation(FRotator(0.f,180.f,0.f));
}

void AGCPlayerCharacter::StandUp()
{
	Super::StandUp();
	// Enable Mouse and Keyboard inputs
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(false);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(false);
	// Allow the camera to move normally
	CameraSpringArm->bUsePawnControlRotation = true;
}

void AGCPlayerCharacter::StoreItem(AChest* Chest)
{
	if(!ItemInHand->IsA(AFood::StaticClass()) || Chest == nullptr)
	{
		return;
	}
	// Detach item from the hand socket
	const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	ItemInHand->GetItemMesh()->DetachFromComponent(DetachmentTransformRules);
	ItemInHand->DisableItem();
	ItemInHand->SetActorLocation(Chest->GetValidStoredPosition());
	ItemInHand->SetActorRotation(Chest->GetValidStoredRotation());
	AGCGameMode * LevelGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(LevelGameMode)
		LevelGameMode->IncrementStoredFood();
	ItemInHand = nullptr;
	bHasItem = false;
	ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
}

void AGCPlayerCharacter::Interact()
{
	if(HasItem())
	{
		AChest* FoundChest;
		int ChestIndex;
		if(InteractiveItems.FindItemByClass<AChest>(&FoundChest, &ChestIndex))
		{
			StoreItem(FoundChest);
		}
		else
		{
			DropItem();
		}
	}
	else if(bSit)
	{
		StandUp();
	}
	else if(InteractiveItems.Num() > 0)
	{
		AInteractiveItem* SelectedItem = InteractiveItems[0];
		if(SelectedItem == nullptr)
		{
			return;
		}
		if(SelectedItem->IsA(AChair::StaticClass()))
		{
			AChair* Chair = Cast<AChair>(SelectedItem);
			SitDown(Chair);
		}
		else if(SelectedItem->IsA(APickableItem::StaticClass()))
		{
			APickableItem* PickableItem = Cast<APickableItem>(SelectedItem);
			GrabItem(PickableItem);
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "Interact with Last Actor");
	}
}
