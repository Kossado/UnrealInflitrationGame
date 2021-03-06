#include "Characters/KnightCharacter.h"

#include "Food/Food.h"
#include "Items/Chair.h"
#include "Managers/GCGameMode.h"
#include "GenericTeamAgentInterface.h"
#include "AI/AIEnemyCharacter.h"
#include "AI/AIEnemyController.h"
#include "HUD/InGameInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/CapsuleComponent.h"



// Sets default values
AKnightCharacter::AKnightCharacter() : Super()
{
	// Create camera stick
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Stick"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 300.f; // Distance between the camera and the character
	CameraSpringArm->bUsePawnControlRotation = true; // Rotate based on the controller

	// Create Camera that will follow the character
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	CameraComponent->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName); // Attach Camera to end on the stick
	CameraComponent->bUsePawnControlRotation = false; // Camera doesn't rotate relative to arm

	// Create second camera stick
	CameraPortraitStick = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("Camera Portrait Stick")));
	CameraPortraitStick->SetupAttachment(RootComponent);
	CameraPortraitStick->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 35.0f), FRotator(0.0f, 180.0f, 0.0f));
	CameraPortraitStick->TargetArmLength = 80.f; // Distance between the camera and the character
	CameraPortraitStick->bDoCollisionTest = false; // Disable collision camera
	
	// Create Camera that will follow the portrait character
	CameraPortraitComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(FName(TEXT("CameraPortrait")));
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
void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool AKnightCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const
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

void AKnightCharacter::SitDown(AChair* Chair)
{
	Super::SitDown(Chair);
	// Disable Mouse and Keyboard inputs
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(true);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(true);
	// Make the camera stay in front of the player
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->SetRelativeRotation(FRotator(0.f,180.f,0.f));
}

void AKnightCharacter::StandUp()
{
	Super::StandUp();
	// Enable Mouse and Keyboard inputs
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(false);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(false);
	// Allow the camera to move normally
	CameraSpringArm->bUsePawnControlRotation = true;
}

void AKnightCharacter::StoreItem(AInteractiveItem* InteractiveChest)
{
	if(!ItemInHand->IsA(AFood::StaticClass()) || InteractiveChest == nullptr)
	{
		return;
	}
	AChest* Chest = Cast<AChest>(InteractiveChest);
	if(Chest == nullptr)
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
	{
		LevelGameMode->IncrementStoredFood();
		LevelGameMode->FoodManager->RemoveFoodInCounterFoodScene(Cast<AFood>(ItemInHand));
	}
	
	ItemInHand = nullptr;
	bCarryItem = false;
	ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
}
	

void AKnightCharacter::Interact()
{
	if(bSit)
	{
		StandUp();
		return;
	}
	// If There is items to interact with
	if(InteractiveItems.Num() > 0)
	{
		// Select the item to interact with based on the distance with the character
		AInteractiveItem* ItemToInteractWith = InteractiveItems[0];
		if(ItemToInteractWith == nullptr)
		{
			return;
		}
		for(AInteractiveItem* Item:InteractiveItems)
		{
			// Exclude ItemInHand from the list
			if(Item != ItemInHand)
			{
				// ItemToInteractWith can be the item in hand, so when it happens change it to an other item
				if(GetDistanceTo(ItemToInteractWith) > GetDistanceTo(Item) || ItemToInteractWith == ItemInHand)
				{
					ItemToInteractWith = Item;
				}
			}
		}
		// If the character has an item, Try to store it in a chest
		if(HasItem())
		{
			if(ItemToInteractWith->IsA(AChest::StaticClass()))
			{
				StoreItem(ItemToInteractWith);
			}
			else if(ItemToInteractWith->IsA(ASpotFood::StaticClass()) && ItemInHand->IsA(AFood::StaticClass()))
			{
				APickableItem* TmpItem = ItemInHand;
				DropItem();
				Cast<ASpotFood>(ItemToInteractWith)->StoreFood(Cast<AFood>(TmpItem));
			}
			else
			{
				DropItem();
			}
		}
		// If the character doesn't have an item, try to do the other interactions
		else
		{
			if(ItemToInteractWith->IsA(AChair::StaticClass()))
			{
				AChair* Chair = Cast<AChair>(ItemToInteractWith);
				SitDown(Chair);
			}
			else if(ItemToInteractWith->IsA(APickableItem::StaticClass()))
			{
				APickableItem* PickableItem = Cast<APickableItem>(ItemToInteractWith);
				GrabItem(PickableItem);
			}
			else if(ItemToInteractWith->IsA(ASpotFood::StaticClass()))
			{
				ASpotFood* SpotFood = Cast<ASpotFood>(ItemToInteractWith);
				GrabItem(SpotFood->TakeFood());
			}
		}
	}
}

