// Fill out your copyright notice in the Description page of Project Settings.


#include "GCCharacter.h"

#include "Chair.h"
#include "Chest.h"
#include "InteractiveItem.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGCCharacter::AGCCharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer),
BaseWalkSpeed(300.f),
CarryWalkSpeedMultiplicator(0.5f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Maximum movement speed of the character
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

// Called when the game starts or when spawned
void AGCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*void AGCCharacter::CarryFood(AFood* FoodToCarry)
{
	if(FoodToCarry)
	{
		FoodToCarry->SetItemProperties(EIS_Interacting);
		//Get the Hand Socket
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("HandSocket"));
		if(HandSocket)
		{
			// Attach food to the hand socket
			HandSocket->AttachActor(FoodToCarry,GetMesh());
		}
		CarriedFood = FoodToCarry;
		ChangeCharacterSpeed(BaseWalkSpeed, CarryWalkSpeedMultiplicator);
	}
}*/

void AGCCharacter::GrabItem(AInteractiveItem* InteractiveItem)
{
	if(InteractiveItem != nullptr)
	{
		InteractiveItem->SetItemProperties(EIS_Interacting);
		//Get the Hand Socket
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("HandSocket"));
		if(HandSocket)
		{
			// Attach Item to the hand socket
			HandSocket->AttachActor(InteractiveItem,GetMesh());
		}
		ItemInHand = InteractiveItem;
		bHasItem = true;
		ChangeCharacterSpeed(BaseWalkSpeed, CarryWalkSpeedMultiplicator);
	}
}

void AGCCharacter::DropItem()
{
	if(ItemInHand)
	{
		// Detach item from the hand socket
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		ItemInHand->GetItemMesh()->DetachFromComponent(DetachmentTransformRules);
		ItemInHand->SetItemProperties(EIS_Movable);
		ItemInHand = nullptr;
		bHasItem = false;
		ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
	}
}

void AGCCharacter::StoreItem()
{
	// Detach item from the hand socket
	const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	ItemInHand->GetItemMesh()->DetachFromComponent(DetachmentTransformRules);
	ItemInHand->SetItemProperties(EIS_Interacting);
	ItemInHand->SetActorLocation(Cast<AChest>(CurrentInteractiveActor)->GetValidStoredPosition());
	ItemInHand->SetActorRotation(ItemInHand->GetActorRotation() + FRotator(90.f,0.f,0.f));
	LevelGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(LevelGameMode)
		LevelGameMode->IncrementStoredFood();
	ItemInHand = nullptr;
	bHasItem = false;
	ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
}

void AGCCharacter::ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator)
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewSpeed * SpeedMultiplicator;
	}
}
/*
void AGCCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(Food && FoodToPick == nullptr)
	{
		FoodToPick = Food;
	}
	AChest* Chest = Cast<AChest>(OtherActor);
	if(Chest)
	{
		ChestInFront = Chest;
	}
	AChair* Chair = Cast<AChair>(OtherActor);
	if(Chair)
	{
		ChairInFront = Chair;
	}
}

void AGCCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(FoodToPick == Food)
	{
		FoodToPick = nullptr;
	}
	AChest* Chest = Cast<AChest>(OtherActor);
	if(Chest == ChestInFront)
	{
		ChestInFront = nullptr;
	}
	AChair* Chair = Cast<AChair>(OtherActor);
	if(Chair == ChairInFront)
	{
		ChairInFront = nullptr;
	}
}

void AGCCharacter::Interact()
{
	// When "E" key is pressed ...
	if(ChairInFront != nullptr && !bSit)
	{
		SitDown();
		return;
	}
	if(bSit)
	{
		StandUp();
		return;
	}
	//... Drop food in hand if not empty handed ...
	if(CarriedFood != nullptr)
	{
		DropFood();
		return;
	}
	if(FoodToPick != nullptr)//... Pick food if there is in front of the character ...
	{
		CarryFood(FoodToPick);
	}
}*/

void AGCCharacter::SitDown()
{
	AChair* Chair = Cast<AChair>(CurrentInteractiveActor);
	if(Chair != nullptr)
	{
		bSit = true;
		GetCharacterMovement()->GravityScale = 0.f;
		SetActorLocation(Chair->GetSitLocation());
		SetActorRotation(Chair->GetSitRotation());
	}
}

void AGCCharacter::StandUp()
{
	bSit = false;
	GetCharacterMovement()->GravityScale = 1.f;
}

/*void AGCCharacter::DropFood()
{
	if(CarriedFood)
	{
		// Detach food from the hand socket
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		CarriedFood->GetItemMesh()->DetachFromComponent(DetachmentTransformRules);
		// Change food state (Re-enable collisions,...)
		if(ChestInFront)
		{
			CarriedFood->SetFoodState(EFS_Stored);
			StoreFood();
		}
		else
		{
			CarriedFood->SetFoodState(EFoodState::EFS_Dropped);
		}
		CarriedFood = nullptr;
		ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
	}
}*/

void AGCCharacter::OnEnterActor(AActor* InteractiveActor)
{
	if(InteractiveActor != nullptr)
	{
		IInteractable* Interactable = Cast<IInteractable>(InteractiveActor);
		if(Interactable != nullptr)
		{
			CurrentInteractiveActor = InteractiveActor;
			CurrentInteractive = Interactable;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "Enter Actor");
		}
	}
}

void AGCCharacter::OnLeaveActor(AActor* InteractiveActor)
{
	if(InteractiveActor == CurrentInteractiveActor)
	{
		CurrentInteractive = nullptr;
		CurrentInteractiveActor = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "Leave Actor");
	}
	if(ItemInHand != nullptr)
	{
		IInteractable* Interactable = Cast<IInteractable>(ItemInHand);
		if(Interactable != nullptr)
		{
			CurrentInteractiveActor = ItemInHand;
			CurrentInteractive = ItemInHand;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "Re-enable Food in hand after Leaving previous actor");
		}
	}
}

