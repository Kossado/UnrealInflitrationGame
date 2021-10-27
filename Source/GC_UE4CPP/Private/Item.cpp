#include "Item.h"

AItem::AItem():Super()
{
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));

	if(ensureMsgf(StaticMesh != nullptr, TEXT("Static Mesh root is null")))
	{
		SetRootComponent(StaticMesh);
	}
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::SetItemProperties(EItemState State)
{
	CurrentItemState = State;
	switch (State)
	{
	case EIS_Interacting:
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case EIS_Movable:
		StaticMesh->SetSimulatePhysics(true);
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case EIS_Immovable:
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case EIS_Disabled:
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		StaticMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);		
		break;
	default:
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		break;
	}
}
