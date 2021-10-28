// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCCharacter.h"

#include "IDetailTreeNode.h"
#include "Items/Chair.h"
#include "Items/Chest.h"
#include "Managers/GCGameMode.h"
#include "Items/InteractiveItem.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGCCharacter::AGCCharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

// Called when the game starts or when spawned
void AGCCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Set Maximum movement speed of the character
	BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SocketBaseCharacter=GetMesh()->GetSocketByName(NameSocketBaseCharacter);
}

// Called to bind functionality to input
void AGCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGCCharacter::GrabItem(APickableItem* PickableItem)
{
	if(PickableItem != nullptr)
	{
		PickableItem->GrabItem();
		//Get the Hand Socket
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("HandSocket"));
		if(HandSocket)
		{
			// Attach Item to the hand socket
			HandSocket->AttachActor(PickableItem,GetMesh());
		}
		ItemInHand = PickableItem;
		bHasItem = true;
		ChangeCharacterSpeed(BaseWalkSpeed, CarryWalkSpeedMultiplicator);
	}
}

void AGCCharacter::DropItem()
{
	if(ItemInHand != nullptr)
	{
		// Detach item from the hand socket
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		ItemInHand->GetItemMesh()->DetachFromComponent(DetachmentTransformRules);
		ItemInHand->DropItem();
		ItemInHand = nullptr;
		bHasItem = false;
		ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
	}
}

void AGCCharacter::ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator)
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewSpeed * SpeedMultiplicator;
	}
}

void AGCCharacter::SitDown(AChair* Chair)
{
	if(!bSit && Chair != nullptr)
	{
		if(!Chair->IsUsed())
		{
			bSit = true;
			ChairUsed = Chair;
			Chair->Use(this);
			GetCharacterMovement()->GravityScale = 0.f;
			SetActorLocation(Chair->GetSitLocation());
			SetActorRotation(Chair->GetSitRotation());
			
		}
	}
}

void AGCCharacter::StandUp()
{
	if(bSit && ChairUsed != nullptr)
	{		
		GetCharacterMovement()->GravityScale = 1.f;
		ChairUsed->Free(this);
		bSit = false;
		ChairUsed = nullptr;
	}
}

void AGCCharacter::OnEnterActor(AInteractiveItem* InteractiveActor)
{
	if(InteractiveActor != nullptr && !InteractiveItems.Contains(InteractiveActor))
	{
		InteractiveItems.Add(InteractiveActor);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White,  FString::Printf(TEXT("Add Interactive Item %s"), *(InteractiveActor->GetName())));
	}
}

void AGCCharacter::OnLeaveActor(AInteractiveItem* InteractiveActor)
{
	if(InteractiveActor != nullptr && InteractiveItems.Contains(InteractiveActor))
	{
		InteractiveItems.Remove(InteractiveActor);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White,  FString::Printf(TEXT("Remove Interactive Item %s"), *(InteractiveActor->GetName())));
	}
}

bool AGCCharacter::IsRotating() const
{
	return  bRotate; 
}

void AGCCharacter::BeginRotate()
{
	bRotate = true;
}

void AGCCharacter::EndRotate()
{
	bRotate = false;
}

