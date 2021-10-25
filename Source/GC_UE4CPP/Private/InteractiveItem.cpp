// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractiveItem::AInteractiveItem()
{
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	RootComponent = StaticMesh;
	
	Trigger = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Sphere Component")));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetSphereRadius(100.f);

}

void AInteractiveItem::SetItemProperties(EItemState State) const
{

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
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		break;
	default:
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		break;
	}
}

// Called when the game starts or when spawned
void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveItem::OnSphereBeginOverlap);
    Trigger->OnComponentEndOverlap.AddDynamic(this, &AInteractiveItem::OnSphereEndOverlap);
	
}

void AInteractiveItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Character = Cast<AGCCharacter>(OtherActor);

	if(Character != nullptr)
	{
		Character->OnEnterActor(this);
	}
}

void AInteractiveItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Character != nullptr)
	{
		Character->OnLeaveActor();
	}
}

FName AInteractiveItem::GetName()
{
	return ItemName;
}

void AInteractiveItem::OnInteract()
{
	if(Character != nullptr)
	{
		// Rotate the character to face the object it is interacting with
		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), GetActorLocation());
		Character->SetActorRotation(FRotator(0.f,LookRotation.Yaw, 0.f));
	}
}

