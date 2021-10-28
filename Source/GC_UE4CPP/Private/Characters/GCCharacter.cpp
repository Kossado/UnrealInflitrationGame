// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCCharacter.h"

#include "Items/Chair.h"
#include "Managers/GCGameMode.h"
#include "Items/InteractiveItem.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGCCharacter::AGCCharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
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
		bCarryItem = true;
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
		bCarryItem = false;
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
	}
}

void AGCCharacter::OnLeaveActor(AInteractiveItem* InteractiveActor)
{
	if(InteractiveActor != nullptr && InteractiveItems.Contains(InteractiveActor))
	{
		InteractiveItems.Remove(InteractiveActor);
	}
}

bool AGCCharacter::IsRotating() const
{
	return  bRotate; 
}

void AGCCharacter::UnSpawn()
{
	if(ItemInHand)
	{
		AFood * FoodInHand = Cast<AFood>(ItemInHand);
		if(FoodInHand != nullptr)
		{
			AGCGameMode * GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			if(GameMode != nullptr)
			{
				if(GameMode->FoodManager == nullptr)
				{
					UE_LOG(LogTemp, Error, TEXT("Food Manager is Null"));
					return;
				}
				GameMode->FoodManager->DestroyFood(FoodInHand);
			}
		}
		else
		{
			ItemInHand->DestroyItem();
		}
	}
}

void AGCCharacter::BeginRotate()
{
	bRotate = true;
}

void AGCCharacter::EndRotate()
{
	bRotate = false;
}

